#include "stdafx.h"
#include "GameContext.h"
#include "Context.h"
#include "GameObjectContainer.h"
#include "MoveContainer.h"
#include "DrawContainer.h"
#include "KeyMapping.h"
#include "PauseMenu.h"

GameContext::GameContext(Context* context)
{
	this->context = context;
	
	moveContainer = new MoveContainer();
	drawContainer = new DrawContainer();
	useContainer = new GameObjectContainer();
	player = new Player(moveContainer, drawContainer,useContainer);
	playerActions.SetPlayer(player);

	keyMappingImporter.Import("./Resources/key-mapping.json");
	KeyMapping::ReloadMapping(keyMappingImporter.GetMapping());


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
}

