#include "stdafx.h"
#include "GameContext.h"
#include "Context.h"
#include "GameObjectContainer.h"
#include "MoveContainer.h"
#include "DrawContainer.h"
#include "KeyMapping.h"
#include "DebugBox2D.h"
#include "PauseMenu.h"
#include "CollisionListener.h"

GameContext::GameContext(Context* context)
{
	this->context = context;

	b2Vec2 gravity(0.f, 0.0f);
	collisionListener = { new CollisionListener() };

	world = { new b2World(gravity) };
	world->SetContactListener(collisionListener);

	moveContainer = new MoveContainer();
	drawContainer = new DrawContainer();
	useContainer = new GameObjectContainer();

	player = new Player(moveContainer, drawContainer, useContainer, world);
}

void GameContext::setMenuPosition()
{
	pauze->setPositions(level->GetViewPortPosition().x, level->GetViewPortPosition().y, context->window.getSize().x, context->window.getSize().y);
}



GameContext::~GameContext()
{
	delete pauze;
	delete player;
	delete levelImporter;
	delete level;
	delete fpsShow;
	delete collisionListener;

	delete moveContainer;
	delete drawContainer;
	delete useContainer;

	pauze = nullptr;
	player = nullptr;
	levelImporter = nullptr;
	level = nullptr;
	fpsShow = nullptr;
	collisionListener = nullptr;

	moveContainer = nullptr;
	drawContainer = nullptr;
	useContainer = nullptr;
}

