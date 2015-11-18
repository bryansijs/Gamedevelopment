#include "stdafx.h"
#include "GameContext.h"

#include "MoveContainer.h"
#include "DrawContainer.h"
#include "KeyMapping.h"

GameContext::GameContext(Context* context)
{
	this->context = context;

	moveContainer = new MoveContainer();
	drawContainer = new DrawContainer();

	player = new Player(moveContainer, drawContainer);
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
