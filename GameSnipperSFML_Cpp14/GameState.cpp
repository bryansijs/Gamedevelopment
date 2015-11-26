#include "stdafx.h"
#include "GameState.h"

#include "StateManager.h"

#include "Context.h"
#include "GameContext.h"
#include "MoveContainer.h"
#include "DrawContainer.h"
#include "input.h"

GameState::GameState(Context* context, StateManager* stateManager)
{
	gameContext = new GameContext(context);
	this->stateManager = stateManager;

	gameContext->levelImporter = new LevelImporter(gameContext->drawContainer, gameContext->useContainer);
	gameContext->levelImporter->Import("./Resources/levels/Level_New.json");
	gameContext->levelImporter->Prepare();

	gameContext->level = gameContext->levelImporter->getLevel();
	gameContext->levelImporter->Clear();

	gameContext->player->GetActions()->SetContainers(gameContext->drawContainer, gameContext->moveContainer, &gameContext->level->tiles);
	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());

	sf::FloatRect rect(gameContext->level->getViewPortX(), gameContext->level->getViewPortY(), gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);
	
	gameContext->view.reset(rect);
	gameContext->context->window.setView(gameContext->view);
}

GameState::~GameState()
{
}

void GameState::Update()
{
	Time::deltaTime = (float)gameContext->deltaClock.restart().asMilliseconds() / 10;
	Time::runningTime += Time::deltaTime;

	gameContext->context->window.clear();

	sf::Vector2f playerPosition = gameContext->player->getPosition();
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
				gameContext->gameInput.CatchInput();
				gameContext->playerInput.CatchInput();
			}
		}
		gameContext->gameInput.ProcessKeyActions();
		gameContext->playerInput.ProcessKeyActions();
		gameContext->level->updateViewPort(worldPosition);
	}

	gameContext->moveContainer->Update();
	gameContext->drawContainer->Draw(&gameContext->context->window);


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