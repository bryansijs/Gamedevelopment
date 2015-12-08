#include "stdafx.h"
#include "GameState.h"

#include "StateManager.h"

#include "Context.h"
#include "GameContext.h"
#include "MoveContainer.h"
#include "DrawContainer.h"
#include "input.h"
#include "GameActions.h"
#include "PlayerActions.h"
#include "AwesomiumHelper.h"
#include "StorylineManager.h"

GameState::GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager)
{
	maincontext = context;
	
	gameActions = new GameActions(this);
	gameContext = new GameContext(context);
	storyline = new AwesomiumHelper{ context->web_core, "file:///Resources/html-game/StoryLine.html", 1000, 50 };

	playerActions.SetPlayer(gameContext->player);

	this->stateManager = stateManager;
	this->levelManager = levelmanager;

	gameContext->levelImporter = new LevelImporter(gameContext->drawContainer, gameContext->useContainer);
	gameContext->levelImporter->Import(std::string("./Resources/levels/").append(this->levelManager->getNextLevelName()));


	gameContext->levelImporter->Prepare();

	gameContext->level = gameContext->levelImporter->getLevel();
	gameContext->levelImporter->Clear();

	playerActions.SetContainers(gameContext->drawContainer, gameContext->moveContainer, &gameContext->level->tiles);
	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());

	sf::FloatRect rect(gameContext->level->getViewPortX(), gameContext->level->getViewPortY(), gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);

	gameContext->view.reset(rect);
	gameContext->context->window.setView(gameContext->view);

	StorylineManager::Add("Let's find a way out!");
	StorylineManager::Add("Use your arrow keys to walk");
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

	if (StorylineManager::Updated())
	{
		storyline->JavaScriptCall("TextUpdate", StorylineManager::GetText());
	}
	sf::Sprite storylineSprite = storyline->GetSprite();
	storylineSprite.setPosition(0, 880);

	gameContext->moveContainer->Update();
	gameContext->drawContainer->Draw(&gameContext->context->window);

	gameContext->context->window.setView(storyview);
	gameContext->context->window.draw(storylineSprite);

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

	gameContext->levelImporter = new LevelImporter(gameContext->drawContainer, gameContext->useContainer);
	gameContext->levelImporter->Clear();
	gameContext->levelImporter->Import(std::string("./Resources/levels/").append(this->levelManager->getNextLevelName()));

	gameContext->levelImporter->Prepare();

	gameContext->level = gameContext->levelImporter->getLevel();
	gameContext->levelImporter->Clear();

	playerActions.SetContainers(gameContext->drawContainer, gameContext->moveContainer, &gameContext->level->tiles);
	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());

	sf::FloatRect rect(gameContext->level->getViewPortX(), gameContext->level->getViewPortY(), gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);

	gameContext->view.reset(rect);
	gameContext->context->window.setView(gameContext->view);

	Update();
}