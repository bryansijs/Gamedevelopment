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
#include "tinydir.h"
#include "Random.h"
#include <vector>
#include <string>

GameState::GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager)
{
	maincontext = context;
	
	gameActions = new GameActions(this);
	gameContext = new GameContext(context);
	storyline = new AwesomiumHelper{ context->web_core, "file:///Resources/html-game/StoryLine.html", 1000, 50 };
	storylineManager = new StorylineManager();

	// Awesomium init
	gameContext->web_core = context->web_core;
	gameContext->webView = gameContext->web_core->CreateWebView(960, 640);

	Loading();

	playerActions = new PlayerActions(gameContext->player);

	this->stateManager = stateManager;
	this->levelManager = levelmanager;
	//in constructor, usually

	gameContext->levelImporter = new LevelImporter(gameContext->drawContainer, gameContext->moveContainer, gameContext->useContainer, gameContext->world);
	gameContext->levelImporter->Import(std::string("./Resources/levels/").append(this->levelManager->getNextLevelName()));

	gameContext->levelImporter->Prepare();

	gameContext->level = gameContext->levelImporter->getLevel();
	gameContext->levelImporter->Clear();

	playerActions->SetContainers(gameContext->drawContainer, gameContext->moveContainer, gameContext->useContainer);
	playerActions->SetWorld(gameContext->world);

	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());
	gameContext->level->End(context, stateManager, levelManager);
	gameContext->level->Story(storylineManager);

	gameContext->player->createBoxDynamic(*gameContext->world);

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

		b2Shape::Type t = b->GetFixtureList()->GetType();
		if (t == b2Shape::e_polygon)
		{
			b2PolygonShape* s = (b2PolygonShape*)b->GetFixtureList()->GetShape();
			sf::ConvexShape convex;
			int vertextCount = s->GetVertexCount();
			convex.setPointCount(vertextCount);
			convex.setFillColor(sf::Color(255, 255, 0, 128));

			convex.setPosition(sf::Vector2f(b->GetPosition().x, b->GetPosition().y));

			for (int i = 0; i < vertextCount; i++)
				convex.setPoint(i, sf::Vector2f(s->GetVertex(i).x, s->GetVertex(i).y));
			gameContext->context->window.draw(convex);
		}
	}
}

void GameState::Update()
{
	Time::deltaTime = static_cast<float>(gameContext->deltaClock.restart().asSeconds());
	Time::deltaTime *= gameContext->gameSpeedMultiplier;
	Time::runningTime += Time::deltaTime;

	gameContext->context->window.clear(sf::Color::White);

	sf::Vector2f playerPosition(gameContext->player->getBody()->GetPosition().x, gameContext->player->getBody()->GetPosition().y);
	sf::Vector2i worldPosition = gameContext->context->window.mapCoordsToPixel(playerPosition);

	if (showFPS)
		gameContext->fpsShow->setFPS(gameContext->level->GetViewPortPosition().x, gameContext->level->GetViewPortPosition().y, gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);
	gameContext->level->draw(&gameContext->context->window, &gameContext->view);

	if (!isPause)
	{
		gameContext->level->update();
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
				if (Input::GetKeyDown("RBracket"))
				{
					gameContext->gameSpeedMultiplier++;
				}

				if (Input::GetKeyDown("LBracket"))
				{
					if (gameContext->gameSpeedMultiplier > 1)
					{
						gameContext->gameSpeedMultiplier--;
					}
				}

				if (Input::GetKeyDown("K")) {
					StartNextLevel();
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
		this->gameContext->world->Step(1, 8, 3);

		DestroyGameObjects();
		gameContext->moveContainer->Update(gameContext->level->GetViewPortPosition());

		if (StorylineManager::Updated())
		{
			storyline->JavaScriptCall("TextUpdate", StorylineManager::GetText());
		}

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

	sf::Sprite storylineSprite = storyline->GetSprite();
	storylineSprite.setPosition(0, 540);
	gameContext->context->window.setView(storyview);
	gameContext->context->window.draw(storylineSprite);


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

	playerActions->SetContainers(gameContext->drawContainer, gameContext->moveContainer, gameContext->useContainer);
	playerActions->SetWorld(gameContext->world);

	gameContext->level->Start(gameContext->player, &gameContext->context->window.getSize());

	sf::FloatRect rect(gameContext->level->getViewPortX(), gameContext->level->getViewPortY(), gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);

	gameContext->view.reset(rect);
	gameContext->context->window.setView(gameContext->view);

	Update();
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