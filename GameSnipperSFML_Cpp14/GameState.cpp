#include "stdafx.h"
#include "GameState.h"

#include "StateManager.h"

#include "Context.h"
#include "GameContext.h"
#include "MoveContainer.h"
#include "DrawContainer.h"
#include "square.h"


GameState::GameState(Context* context, StateManager* stateManager)
{
	gameContext = new GameContext(context);
	this->stateManager = stateManager;

	gameContext->levelImporter = new LevelImporter(gameContext->drawContainer, gameContext->useContainer, gameContext->world);
	gameContext->levelImporter->Import("./Resources/levels/CollideTest.json");
	gameContext->levelImporter->Prepare();

	gameContext->level = gameContext->levelImporter->getLevel();
	gameContext->levelImporter->Clear();

	gameContext->playerActions.SetContainers(gameContext->drawContainer, gameContext->moveContainer, &gameContext->level->groundTiles);
	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());

	sf::FloatRect rect(gameContext->level->getViewPortX(), gameContext->level->getViewPortY(), gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);
	
	gameContext->view.reset(rect);
	gameContext->context->window.setView(gameContext->view);

	s = { new square(context) };
	s->createBoxDynamic(*gameContext->world);
	s->setPosition(b2Vec2(gameContext->player->getPositionX() + 1000, gameContext->player->getPositionY() + 1000));
	
	s2 = { new square(context) };
	s2->createBoxStatic(*gameContext->world);
	s2->setPosition(b2Vec2(gameContext->player->getPositionX() + 1000, gameContext->player->getPositionY() + 1000));
}

GameState::~GameState()
{
}

void GameState::Update()
{
	Time::deltaTime = (float)gameContext->deltaClock.restart().asSeconds();
	Time::runningTime += Time::deltaTime;

	gameContext->context->window.clear(sf::Color::White);

	sf::Vector2f playerPosition(gameContext->player->getPosition().x, gameContext->player->getPosition().y);
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


	sf::Sprite Sprite;
	Sprite.setTexture(s->BoxTexture);
	Sprite.setOrigin(16.f, 16.f);
	Sprite.setPosition(s->getBody()->GetPosition().x, s->getBody()->GetPosition().y);
	Sprite.setRotation(s->getBody()->GetAngle() * 180 / b2_pi);

	gameContext->context->window.draw(Sprite);

	sf::Sprite Sprite2;
	Sprite2.setTexture(s2->BoxTexture);
	Sprite2.setOrigin(16.f, 16.f);
	Sprite2.setPosition(1 * s2->getBody()->GetPosition().x, 1 * s2->getBody()->GetPosition().y);
	Sprite2.setRotation(s2->getBody()->GetAngle() * 180 / b2_pi);

	gameContext->context->window.draw(Sprite2);



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