#include "stdafx.h"
#include "GameState.h"
#include "StateManager.h"
#include "KeyMapping.h"
#include <iostream>
#include "Context.h"
#include "GameContext.h"
#include "MoveContainer.h"
#include "DrawContainer.h"
#include "WinState.h"
#include "LoseState.h"
#include "MenuState.h"
#include "square.h"

GameState::GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager)
{
	maincontext = context;
	gameContext = new GameContext(context);
	this->stateManager = stateManager;
	this->levelManager = levelmanager;

	gameContext->levelImporter = new LevelImporter(gameContext->drawContainer,gameContext->moveContainer, gameContext->useContainer, gameContext->world);
	gameContext->levelImporter->Import(std::string("./Resources/levels/").append(this->levelManager->getNextLevelName()));

	//gameContext->levelImporter = new LevelImporter(gameContext->drawContainer, gameContext->moveContainer, gameContext->useContainer);
	//gameContext->levelImporter->Import("./Resources/levels/Level_New.json");

	gameContext->levelImporter->Prepare();

	gameContext->level = gameContext->levelImporter->getLevel();
	gameContext->levelImporter->Clear();

	gameContext->playerActions.SetContainers(gameContext->drawContainer, gameContext->moveContainer);
	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());
	gameContext->level->End(context, stateManager, levelManager);

	gameContext->player->createBoxDynamic(*gameContext->world);

	sf::FloatRect rect(gameContext->level->getViewPortX(), gameContext->level->getViewPortY(), gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);

	gameContext->view.reset(rect);
	gameContext->context->window.setView(gameContext->view);
}

GameState::~GameState()
{
	delete(gameContext);
	delete(levelManager);
}

void GameState::Update()
{
	Time::deltaTime = (float)gameContext->deltaClock.restart().asSeconds();
	Time::runningTime += Time::deltaTime;

	gameContext->context->window.clear(sf::Color::White);

	sf::Vector2f playerPosition(gameContext->player->getBody()->GetPosition().x, gameContext->player->getBody()->GetPosition().y);
	sf::Vector2i worldPosition = gameContext->context->window.mapCoordsToPixel(playerPosition);

	gameContext->level->draw(&gameContext->context->window, &gameContext->view);
	gameContext->level->update();

	if (gameContext->level->getDoEvents()) {
		while (gameContext->context->window.pollEvent(gameContext->event)) {
			if (gameContext->event.type == sf::Event::Closed)
			{
				gameContext->context->window.close();
				stateManager->PopState();
				return;
			}

			if (gameContext->event.type == sf::Event::KeyPressed || gameContext->event.type == sf::Event::KeyReleased)
			{
				Input::EventOccured(gameContext->event);
				gameContext->playerInput.CatchInput();

				if (Input::GetKeyDown("K")) {
					StartNextLevel();
				}


				if (isPause)
					this->MenuEnd(gameContext->pauze->KeyHandler());

				if (Input::GetKeyUp(KeyMapping::GetKey("pause"))) {
					isPause = !isPause;
					gameContext->pauze->playEffect();
					gameContext->level->pauseMusic(!isPause);
					if (isPause)
						gameContext->setMenuPosition();
				}


			}
		}
		if (!isPause)
		{
			gameContext->playerActions.ProcessActions(gameContext->playerInput.GetActiveKeys());
			gameContext->level->updateViewPort(worldPosition);
		}
	}
	else
	{
		gameContext->player->getBody()->SetLinearVelocity(b2Vec2(0, 0));
	}




	if (isPause)
	{
		gameContext->pauze->draw(gameContext->context->window);
	}


	this->gameContext->world->Step(1, 8, 3);

	if (!isPause)
	{
		gameContext->moveContainer->Update(gameContext->level->GetViewPortPosition());

	}
	gameContext->drawContainer->Draw(&gameContext->context->window);
	gameContext->level->drawRoof(&gameContext->context->window, &gameContext->view);

	if (!terminate) {
		gameContext->context->window.setView(gameContext->view);
	}


	gameContext->context->window.display();

	if (gameContext->player->getHealth() <= 0)
	{
		sf::Image screenshot = gameContext->context->window.capture();
		screenshot.saveToFile("./Resources/menuHTML/images/hold.png");

		LoseState* loseState = new LoseState(gameContext->context, stateManager, levelManager);
		stateManager->AddState(loseState);
		stateManager->StartNextState();
	}

	if (terminate)
	{
		delete gameContext;
	}
}

void GameState::Terminate()
{
	terminate = true;
}

void GameState::StartNextLevel()
{
	delete(gameContext);

	gameContext = new GameContext(maincontext);

	gameContext->levelImporter = new LevelImporter(gameContext->drawContainer, gameContext->moveContainer, gameContext->useContainer, gameContext->world);
	gameContext->levelImporter->Import(std::string("./Resources/levels/").append(this->levelManager->getNextLevelName()));

	gameContext->levelImporter->Prepare();

	gameContext->level = gameContext->levelImporter->getLevel();
	gameContext->levelImporter->Clear();

	gameContext->playerActions.SetContainers(gameContext->drawContainer, gameContext->moveContainer);
	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());

	sf::FloatRect rect(gameContext->level->getViewPortX(), gameContext->level->getViewPortY(), gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);

	gameContext->view.reset(rect);
	gameContext->context->window.setView(gameContext->view);

	Update();
}

void GameState::MenuEnd(int option)
{
	switch (option)	{
		case 0: {
			isPause = false;
			gameContext->pauze->playEffect();
			gameContext->level->pauseMusic(!isPause); }
			break;
		case 1: {
			terminate = true;
			MenuState* menu = new MenuState{ gameContext->context, stateManager, levelManager };
			stateManager->AddState(menu);
			stateManager->StartNextState();
			break; }
		case 2: {
			exit(0); }
			break;
		default:
			break;
	}

}
