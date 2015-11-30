#include "stdafx.h"
#include "GameState.h"

#include "StateManager.h"
#include <iostream>
#include "Context.h"
#include "GameContext.h"
#include "MoveContainer.h"
#include "DrawContainer.h"
#include "square.h"


GameState::GameState(Context* context, StateManager* stateManager)
{
	gameContext = new GameContext(context);
	this->stateManager = stateManager;

	gameContext->levelImporter = new LevelImporter(gameContext->drawContainer,gameContext->moveContainer, gameContext->useContainer, gameContext->world);
	gameContext->levelImporter->Import("./Resources/levels/Level_New.json");

	gameContext->levelImporter->Prepare();

	gameContext->level = gameContext->levelImporter->getLevel();
	gameContext->levelImporter->Clear();

	gameContext->playerActions.SetContainers(gameContext->drawContainer, gameContext->moveContainer, &gameContext->level->groundTiles);
	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());

	gameContext->player->createBoxDynamic(*gameContext->world);

	sf::FloatRect rect(gameContext->level->getViewPortX(), gameContext->level->getViewPortY(), gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);
	
	gameContext->view.reset(rect);
	gameContext->context->window.setView(gameContext->view);

}

GameState::~GameState()
{
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
			}
		}

		gameContext->playerActions.ProcessActions(gameContext->playerInput.GetActiveKeys());
		gameContext->level->updateViewPort(worldPosition);
	}

	this->gameContext->world->Step(1 / 60.f, 8, 3);

	gameContext->moveContainer->Update();
	gameContext->drawContainer->Draw(&gameContext->context->window);

	gameContext->level->drawRoof(&gameContext->context->window, &gameContext->view);
	gameContext->context->window.setView(gameContext->view);


	///////////////////////////////////// Guus


	//for (b2Body* b = gameContext->world->GetBodyList(); b; b = b->GetNext()) {
	//	sf::RectangleShape rectangle(sf::Vector2f(32, 32));
	//	rectangle.setPosition(sf::Vector2f(b->GetPosition().x, b->GetPosition().y));
	//	rectangle.setOutlineThickness(0);
	//	rectangle.setFillColor(sf::Color(180, 100, 100, 200));
	//	gameContext->context->window.draw(rectangle);
	//}



	///////////////////////////////////// End Guus Box2d Test

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