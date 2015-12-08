#include "stdafx.h"
#include "GameContext.h"
#include "GameObjectContainer.h"
#include "MoveContainer.h"
#include "DrawContainer.h"

#include "KeyMapping.h"
#include "DebugBox2D.h"
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

GameContext::~GameContext()
{
	delete player;
	delete levelImporter;
	delete level;
}
