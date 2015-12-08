#include "stdafx.h"
#include "GameState.h"

#include "StateManager.h"
#include <iostream>
#include "Context.h"
#include "GameContext.h"
#include "MoveContainer.h"
#include "DrawContainer.h"

#include "square.h"

#include "input.h"
#include "GameActions.h"
#include "PlayerActions.h"

GameState::GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager)
{
	maincontext = context;
	
	gameActions = new GameActions(this);

	gameContext = new GameContext(context);

	playerActions.SetPlayer(gameContext->player);

	this->stateManager = stateManager;
	this->levelManager = levelmanager;

	gameContext->levelImporter = new LevelImporter(gameContext->drawContainer,gameContext->moveContainer, gameContext->useContainer, gameContext->world);
	gameContext->levelImporter->Import(std::string("./Resources/levels/").append(this->levelManager->getNextLevelName()));

	//gameContext->levelImporter = new LevelImporter(gameContext->drawContainer, gameContext->moveContainer, gameContext->useContainer);
	//gameContext->levelImporter->Import("./Resources/levels/Level_New.json");

	gameContext->levelImporter->Prepare();

	gameContext->level = gameContext->levelImporter->getLevel();
	gameContext->levelImporter->Clear();

	playerActions.SetContainers(gameContext->drawContainer, gameContext->moveContainer);
	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());

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
	Time::deltaTime = static_cast<float>(gameContext->deltaClock.restart().asSeconds());
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
				playerActions.CatchInput();
			}

			if (gameContext->event.type == sf::Event::KeyPressed)
			{
				gameActions->CatchSingleInput();
				gameActions->ProcessActions();
			}
		}
		playerActions.ProcessActions();
		gameContext->level->updateViewPort(worldPosition);
	}
	else
	{
		gameContext->player->getBody()->SetLinearVelocity(b2Vec2(0, 0));
	}

	this->gameContext->world->Step(1, 8, 3);

	gameContext->moveContainer->Update(gameContext->level->GetViewPortPosition());
	gameContext->drawContainer->Draw(&gameContext->context->window);

	gameContext->level->drawRoof(&gameContext->context->window, &gameContext->view);
	gameContext->context->window.setView(gameContext->view);

	gameContext->context->window.display();

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

	playerActions.SetContainers(gameContext->drawContainer, gameContext->moveContainer);
	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());

	sf::FloatRect rect(gameContext->level->getViewPortX(), gameContext->level->getViewPortY(), gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);

	gameContext->view.reset(rect);
	gameContext->context->window.setView(gameContext->view);

	Update();
}
