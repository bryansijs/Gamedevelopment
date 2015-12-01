#include "stdafx.h"
#include "GameState.h"

#include "StateManager.h"

#include "Context.h"
#include "GameContext.h"
#include "MoveContainer.h"
#include "DrawContainer.h"

#include "KeyMapping.h"

GameState::GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager)
{
	maincontext = context;
	gameContext = new GameContext(context);
	this->stateManager = stateManager;
	this->levelManager = levelmanager;

	gameContext->levelImporter = new LevelImporter(gameContext->drawContainer, gameContext->useContainer);
	gameContext->levelImporter->Import(std::string("./Resources/levels/").append(this->levelManager->getNextLevelName()));


	gameContext->levelImporter->Prepare();

	gameContext->level = gameContext->levelImporter->getLevel();
	gameContext->levelImporter->Clear();

	gameContext->playerActions.SetContainers(gameContext->drawContainer, gameContext->moveContainer, &gameContext->level->tiles);
	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());

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
				gameContext->playerInput.CatchInput();



				if (Input::GetKeyUp(KeyMapping::GetKey("pause"))) {
					std::cout << isPause << std::endl;
					isPause = !isPause;

					gameContext->level->pauseMusic(isPause);

					if (isPause)
					{
						float x = gameContext->level->GetViewPortPosition().x + gameContext->context->window.getSize().x / 4;
						float y = gameContext->level->GetViewPortPosition().y + gameContext->context->window.getSize().y / 4;
						gameContext->pauzeText.setPosition(x, y);
						gameContext->pauseSound.play();
					}

				}



				if (Input::GetKeyDown("K")) {
					StartNextLevel();
				}
			}
		}

		if (!isPause) {
			gameContext->playerActions.ProcessActions(gameContext->playerInput.GetActiveKeys());
			gameContext->level->updateViewPort(worldPosition);
		}
	}


	if (!isPause) {
		gameContext->moveContainer->Update();
	}
	gameContext->drawContainer->Draw(&gameContext->context->window);


	gameContext->context->window.setView(gameContext->view);

	if (isPause)
	{
		gameContext->context->window.draw(gameContext->pauzeText);
	}


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

	gameContext->levelImporter = new LevelImporter(gameContext->drawContainer, gameContext->useContainer);
	gameContext->levelImporter->Clear();
	gameContext->levelImporter->Import(std::string("./Resources/levels/").append(this->levelManager->getNextLevelName()));

	gameContext->levelImporter->Prepare();

	gameContext->level = gameContext->levelImporter->getLevel();
	gameContext->levelImporter->Clear();

	gameContext->playerActions.SetContainers(gameContext->drawContainer, gameContext->moveContainer, &gameContext->level->tiles);
	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());

	sf::FloatRect rect(gameContext->level->getViewPortX(), gameContext->level->getViewPortY(), gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);
	
	gameContext->view.reset(rect);
	gameContext->context->window.setView(gameContext->view);

	Update();
}
