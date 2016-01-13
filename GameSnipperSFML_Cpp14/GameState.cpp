#include "stdafx.h"
#include "GameState.h"
#include "StateManager.h"
#include "KeyMapping.h"
#include "Context.h"
#include "GameContext.h"
#include "MoveContainer.h"
#include "DrawContainer.h"
#include "input.h"
#include "GameActions.h"
#include "PlayerActions.h"
#include "AwesomiumHelper.h"
#include "StorylineManager.h"
#include "LoseState.h"
#include "MenuState.h"
#include <iterator>
#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>
#include "HUD.h"
#include "tinydir.h"
#include "Random.h"
#include <vector>
#include <string>
#include "WinState.h"
#include "GameObjectContainer.h"

GameState::GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager, ScoreManager* scoreManager, bool next)
{
	maincontext = context;
	
	gameContext = new GameContext(context);

	hud = new HUD{ gameContext };

	gameActions = new GameActions(this, gameContext);

	storyline = new AwesomiumHelper{ context->web_core, "file:///Resources/html-game/StoryLine.html", 960, 36 };
	storylineManager = new StorylineManager();

	// Awesomium init
	gameContext->web_core = context->web_core;
	gameContext->webView = gameContext->web_core->CreateWebView(960, 640);

	Loading();

	playerActions = new PlayerActions(gameContext->player);

	this->stateManager = stateManager;
	this->levelManager = levelmanager;
	this->scoreManager = scoreManager;
	//in constructor, usually


	gameContext->levelImporter = new LevelImporter(gameContext->drawContainer, gameContext->moveContainer, gameContext->useContainer, gameContext->world);
	if (next)
		gameContext->levelImporter->Import(std::string("./Resources/levels/").append(this->levelManager->getNextLevelName()));
	else
		gameContext->levelImporter->Import(std::string("./Resources/levels/").append(this->levelManager->getCurrentLevel()));

	gameContext->levelImporter->Prepare();

	gameContext->levelImporter->updateLevel();
	gameContext->level = gameContext->levelImporter->getLevel();
	gameContext->levelImporter->Clear();

	playerActions->SetContainers(gameContext->drawContainer, gameContext->moveContainer, gameContext->useContainer);
	playerActions->SetWorld(gameContext->world);
	playerActions->SetContext(gameContext);

	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());

	gameContext->level->End(context, stateManager, levelManager, scoreManager);
	gameContext->level->Story(storylineManager);

	gameContext->player->createBoxDynamicForPlayers(*gameContext->world);

	b2Filter f = gameContext->player->getBody()->GetFixtureList()->GetFilterData();
	f.categoryBits = 0x0004;

	gameContext->player->getBody()->GetFixtureList()->SetFilterData(f);
	sf::FloatRect rect(gameContext->level->getViewPortX(), gameContext->level->getViewPortY(), gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);

	DoneLoading();

	gameContext->view.reset(rect);
	gameContext->context->window.setView(gameContext->view);

	storyview.setSize(960, 640);
	storyview.setCenter(480, 320);

	StorylineManager::Add("Let's find a way out!");
	StorylineManager::Add("Use your arrow keys to walk");
}

GameState::~GameState()
{
	delete(gameContext);
	delete(levelManager);
}

void GameState::DestroyGameObjects()
{
	std::vector<b2Body*> gameObjectScheduledForRemoval;

	for (b2Body* body = gameContext->world->GetBodyList(); body; body = body->GetNext()) {
		if (body->GetUserData() != nullptr)
		{
			GameObject* data = static_cast<GameObject*>(body->GetUserData());

			if (data->isFlaggedForDelete)
			{
				gameObjectScheduledForRemoval.push_back(body);
			}
		}
	}

	for (int i = 0; i < gameObjectScheduledForRemoval.size(); i++)
	{
		gameContext->world->DestroyBody(gameObjectScheduledForRemoval[i]);
	}

	gameObjectScheduledForRemoval.clear();
}

void GameState::DebugBodies()
{
	for (b2Body* b = gameContext->world->GetBodyList(); b; b = b->GetNext()) {

	

		for (b2Fixture* fix = b->GetFixtureList(); fix; fix = fix->GetNext()) {

			b2Shape::Type t = fix->GetType();
			if (t == b2Shape::e_polygon)
			{
				b2PolygonShape* s = (b2PolygonShape*)fix->GetShape();
				sf::ConvexShape convex;
				int vertextCount = s->GetVertexCount();

				if (vertextCount == 3) continue;

				convex.setPointCount(vertextCount);
				convex.setFillColor(sf::Color(255, 255, 0, 128));

				convex.setPosition(sf::Vector2f(b->GetPosition().x, b->GetPosition().y));

				for (int i = 0; i < vertextCount; i++)
					convex.setPoint(i, sf::Vector2f(s->GetVertex(i).x, s->GetVertex(i).y));

				gameContext->context->window.draw(convex);
			}
		}
	}
}

void GameState::Update()
{
	DestroyGameObjects();
	Time::deltaTime = static_cast<float>(gameContext->deltaClock.restart().asSeconds());
	Time::deltaTime *= gameContext->gameSpeedMultiplier;
	Time::runningTime += Time::deltaTime;

	if (gameContext->player->getHealth() <= 0)
	{
		sf::Image screenshot = gameContext->context->window.capture();

		LoseState* loseState = new LoseState(gameContext->context, stateManager, levelManager, screenshot, scoreManager);
		stateManager->AddState(loseState);
		stateManager->PopState();
	}

	gameContext->context->window.clear(sf::Color::White);

	sf::Vector2f playerPosition(gameContext->player->getBody()->GetPosition().x, gameContext->player->getBody()->GetPosition().y);
	sf::Vector2i worldPosition = gameContext->context->window.mapCoordsToPixel(playerPosition);

	if (showFPS)
		gameContext->fpsShow->setFPS(gameContext->level->GetViewPortPosition().x, gameContext->level->GetViewPortPosition().y, gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);
	gameContext->level->draw(&gameContext->context->window, &gameContext->view);

	if (!isPause)
	{
		DestroyGameObjects();
	//	gameContext->level->update();
	}

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
				playerActions->CatchInput();
			}

			if (gameContext->event.type == sf::Event::KeyPressed && !isPause)
			{
				gameActions->CatchSingleInput();
				gameActions->ProcessActions();
			}

			if (gameContext->event.type == sf::Event::KeyPressed)
			{
				if (Input::GetKeyDown(KeyMapping::GetKey("gamespeed-up")))
				{
					if (gameContext->gameSpeedMultiplier < 2)
					{
						gameContext->gameSpeedMultiplier++;
					}
				}

				if (Input::GetKeyDown(KeyMapping::GetKey("gamespeed-down")))
				{
					if (gameContext->gameSpeedMultiplier > 1)
					{
						gameContext->gameSpeedMultiplier--;
					}
				}

				if (Input::GetKeyDown(KeyMapping::GetKey("damage-up")))
				{
					gameContext->damageMultiplier++;
				}

				if (Input::GetKeyDown(KeyMapping::GetKey("damage-down")))
				{
					if (gameContext->damageMultiplier > 1)
					{
						gameContext->damageMultiplier--;
					}
				}

				if (Input::GetKeyDown("K")) {
					StartNextLevel();
				}
				if (Input::GetKeyDown("Y")) {
					StartWinState();
				}

				if (isPause)
					this->MenuEnd(gameContext->pauze->KeyHandler());

				if (Input::GetKeyDown(KeyMapping::GetKey("escape"))) {
					isPause = !isPause;
					gameContext->pauze->playEffect();
					gameContext->level->pauseMusic(!isPause);
					if (isPause)
						gameContext->setMenuPosition();
				}

				if (Input::GetKeyDown(KeyMapping::GetKey("fps"))) {
					showFPS = !showFPS;
				}
			}
		}

		if (!isPause)
		{
			playerActions->ProcessActions();
			gameContext->level->updateViewPort(worldPosition);
		}

	}
	else
	{
		gameContext->player->getBody()->SetLinearVelocity(b2Vec2(0, 0));
	}

	//DebugBodies();

	if (!isPause)
	{
		float speed = 1;
		float count = 0;
		float point = speed / Time::deltaTime;
		while (point > count) {
			this->gameContext->world->Step(Time::deltaTime, 6, 6);
			count++;
		}

		DestroyGameObjects();

		gameContext->moveContainer->Update(gameContext->level->GetViewPortPosition());
		gameContext->useContainer->Update();
		if (StorylineManager::Updated())
		{
			storyline->JavaScriptCall("TextUpdate", StorylineManager::GetText());
		}

		hud->Update();
	}
	gameContext->drawContainer->Draw(&gameContext->context->window, gameContext->level->GetViewPortPosition());
	gameContext->level->drawRoof(&gameContext->context->window, &gameContext->view);


	if (showFPS ) {
		gameContext->fpsShow->draw(gameContext->context->window);
	}
	
	if(isPause)
	{
		gameContext->pauze->draw(gameContext->context->window);
	}
	
	// draw storyline
	sf::Sprite storylineSprite = storyline->GetSprite();
	storylineSprite.setPosition(0, 540);
	gameContext->context->window.setView(storyview);
	gameContext->context->window.draw(storylineSprite);

	// draw hud
	gameContext->context->window.setView(hud->view);
	gameContext->context->window.draw(hud->awesomium->GetSprite());

	if (!terminate) {
		gameContext->context->window.setView(gameContext->view);
	}

	gameContext->context->window.display();

	if (terminate)
	{
		delete gameContext;
		delete playerActions;
		delete gameActions;
		delete hud;
		delete storyline;
		delete loadingScreen;
		delete storylineManager;

		gameContext = nullptr;
		playerActions = nullptr;
		gameActions = nullptr;
		hud = nullptr;
		storyline = nullptr;
		loadingScreen = nullptr;
		storylineManager = nullptr;
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

	gameContext->levelImporter->updateLevel();
	gameContext->level = gameContext->levelImporter->getLevel();
	gameContext->levelImporter->Clear();

	playerActions->SetContainers(gameContext->drawContainer, gameContext->moveContainer, gameContext->useContainer);
	playerActions->SetWorld(gameContext->world);

	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());

	sf::FloatRect rect(gameContext->level->getViewPortX(), gameContext->level->getViewPortY(), gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);

	gameContext->view.reset(rect);
	gameContext->context->window.setView(gameContext->view);

	Update();
}

void GameState::StartWinState()
{
	sf::Image screenshot = gameContext->context->window.capture();
	

	WinState* winState = new WinState(gameContext->context, stateManager, levelManager, screenshot,scoreManager);
	stateManager->AddState(winState);
	stateManager->StartNextState();
}

void GameState::MenuEnd(int option)
{
	switch (option) {
	case 0: {
		isPause = false;
		gameContext->pauze->playEffect();
		gameContext->level->pauseMusic(!isPause); }
			break;
	case 1: {
		terminate = true;
		MenuState* menu = new MenuState{ gameContext->context, stateManager, levelManager, scoreManager};
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

void GameState::Loading()
{
	gameContext->loading = true;
	
	loadingScreen = new AwesomiumHelper{ maincontext->web_core, "file:///Resources/menuHTML/loading.html", 960, 640 };
	loadingScreen->JavaScriptCall("loadAd", GetAd());
	loadingScreen->JavaScriptCall("loadTip", GetTip());

	DrawLoadingScreen();
}

void GameState::DoneLoading()
{
	delete loadingScreen;
	loadingScreen = nullptr;

	loadingScreen = new AwesomiumHelper{ maincontext->web_core, "file:///Resources/menuHTML/doneLoading.html", 960, 640 };
	loadingScreen->JavaScriptCall("loadAd", GetAd());
	loadingScreen->JavaScriptCall("loadTip", GetTip());

	DrawLoadingScreen();

	while (gameContext->loading)
	{
		while (gameContext->context->window.pollEvent(gameContext->event)) {
			if (gameContext->event.type == sf::Event::Closed)
			{
				gameContext->context->window.close();
				stateManager->PopState();
				return;
			}

			if (gameContext->event.type == sf::Event::KeyPressed)
			{
				gameContext->loading = false;
			}
		}
	}
}

void GameState::DrawLoadingScreen()
{
	sf::Sprite loadingSprite = loadingScreen->GetSprite();
	loadingSprite.setPosition(0, 0);
	loadingView.setSize(960, 640);
	loadingView.setCenter(480, 320);
	gameContext->context->window.setView(loadingView);
	gameContext->context->window.draw(loadingSprite);
	gameContext->context->window.display();
}

std::string GameState::GetAd()
{
	std::vector<std::string> ads = GetFilesInDirectory("./Resources/ads/");

	if (ads.size() > 0)
	{
		return ads[Random::Number(0, (ads.size() - 1))];
	}
	
	return "";
}

std::string GameState::GetTip()
{
	std::vector<std::string> tips;
	
	std::ifstream tipsFile;
	tipsFile.open("./Resources/tips.txt");
	if (tipsFile.is_open())
	{
		string line;
		while (getline(tipsFile, line)) {
			tips.push_back(line);
		}
	}

	if (tips.size() > 0)
	{
		return tips[Random::Number(0, (tips.size() - 1))];
	}
	
	return "";
}

std::vector<std::string> GameState::GetFilesInDirectory(const char* directory)
{
	std::vector<std::string> files;

	tinydir_dir dir;
	tinydir_open(&dir, directory);

	while (dir.has_next)
	{
		tinydir_file file;
		tinydir_readfile(&dir, &file);

		if (!file.is_dir)
		{
			files.push_back(file.name);
		}

		tinydir_next(&dir);
	}

	tinydir_close(&dir);
	
	return files;
}
