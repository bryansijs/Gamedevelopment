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
		sf::RectangleShape rectangle(sf::Vector2f(32, 32));
		rectangle.setPosition(sf::Vector2f(b->GetPosition().x, b->GetPosition().y));
		rectangle.setOutlineThickness(0);
		rectangle.setFillColor(sf::Color(180, 100, 100, 200));
		gameContext->context->window.draw(rectangle);
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
				if (Input::GetKeyDown("Add"))
				{
					gameContext->gameSpeedMultiplier++;
				}

				if (Input::GetKeyDown("Subtract"))
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
	
	gameContext->drawContainer->Draw(&gameContext->context->window);
	gameContext->level->drawRoof(&gameContext->context->window, &gameContext->view);


	if (showFPS ) {
		//gameContext->fpsShow->setFPS(gameContext->level->GetViewPortPosition().x, gameContext->level->GetViewPortPosition().y, gameContext->context->window.getSize().x, gameContext->context->window.getSize().y);
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

	GetAd();

	ReloadUI("file:///Resources/menuHTML/loading.html");
	CreateTexture();
	DrawUI();
}

void GameState::DoneLoading()
{
	ReloadUI("file:///Resources/menuHTML/doneLoading.html");
	CreateTexture();
	DrawUI();

	while (gameContext->loading)
	{
		while (gameContext->context->window.pollEvent(gameContext->event)) {
			if (gameContext->event.type == sf::Event::KeyPressed)
			{
				gameContext->loading = false;
			}
		}
	}
}

void GameState::ReloadUI(char const* path)
{
	Awesomium::WebURL url(Awesomium::WSLit(path));
	gameContext->webView->LoadURL(url);
	gameContext->webView->SetTransparent(true);

	while (gameContext->webView->IsLoading())
	{
		gameContext->web_core->Update();
	}

	Sleep(100);
	gameContext->web_core->Update();
}

void GameState::DrawUI()
{
	sf::Sprite ui(gameContext->texture);
	gameContext->texture.update(gameContext->pixels);
	gameContext->context->window.draw(ui);
	gameContext->context->window.display();
}

void GameState::CreateTexture()
{
	gameContext->surface = static_cast<Awesomium::BitmapSurface*>(gameContext->webView->surface());

	gameContext->texture.create(960, 640);
	gameContext->pixels = new sf::Uint8[gameContext->context->window.getSize().x * gameContext->context->window.getSize().y * 4];

	const unsigned char* tempBuffer = gameContext->surface->buffer();

	for (register int i = 0; i < 960 * 640 * 4; i += 4) {
		gameContext->pixels[i] = tempBuffer[i + 2];
		gameContext->pixels[i + 1] = tempBuffer[i + 1];
		gameContext->pixels[i + 2] = tempBuffer[i];
		gameContext->pixels[i + 3] = tempBuffer[i + 3];
	}
}

void GameState::GetAd()
{
	
}
