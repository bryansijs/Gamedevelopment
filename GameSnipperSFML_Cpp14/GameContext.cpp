#include "stdafx.h"
#include "GameContext.h"
#include "GameObjectContainer.h"
#include "MoveContainer.h"
#include "DrawContainer.h"
#include "KeyMapping.h"
#include "DebugBox2D.h"

GameContext::GameContext(Context* context)
{
	this->context = context;
	b2Vec2 gravity(0.f, 0.0f);
	world = { new b2World(gravity) };

	moveContainer = new MoveContainer();
	drawContainer = new DrawContainer();
	useContainer = new GameObjectContainer();
	player = new Player(moveContainer, drawContainer,useContainer, world);
	playerActions.SetPlayer(player);

	keyMappingImporter.Import("./Resources/key-mapping.json");
	KeyMapping::ReloadMapping(keyMappingImporter.GetMapping());
}

GameContext::~GameContext()
{
	delete player;
	delete levelImporter;
	delete level;
}
