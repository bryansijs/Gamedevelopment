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
#include "LoseState.h"
#include "MenuState.h"
#include <iterator>
#include "DebugBox2D.h"
#include <Box2D\Box2D.h>
#include <Box2D\Common\b2Draw.h>
DebugBox2D fooDrawInstance;
GameState::GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager)
{
	maincontext = context;
	
	gameActions = new GameActions(this);

	gameContext = new GameContext(context);

	playerActions = new PlayerActions(gameContext->player);

	this->stateManager = stateManager;
	this->levelManager = levelmanager;





	//in constructor, usually

	this->gameContext->world->SetDebugDraw(&fooDrawInstance);
	fooDrawInstance.SetFlags(b2Draw::e_shapeBit);

	gameContext->levelImporter = new LevelImporter(gameContext->drawContainer, gameContext->moveContainer, gameContext->useContainer, gameContext->world);
	gameContext->levelImporter->Import(std::string("./Resources/levels/").append(this->levelManager->getNextLevelName()));

	gameContext->levelImporter->Prepare();

	gameContext->level = gameContext->levelImporter->getLevel();
	gameContext->levelImporter->Clear();

	playerActions->SetContainers(gameContext->drawContainer, gameContext->moveContainer, gameContext->useContainer);
	playerActions->SetWorld(gameContext->world);

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

	DebugBodies();



	if (!isPause)
	{
		this->gameContext->world->Step(1, 8, 3);

		DestroyGameObjects();
		gameContext->moveContainer->Update(gameContext->level->GetViewPortPosition());
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



