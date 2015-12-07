#include "stdafx.h"
#include "GameContext.h"
#include "GameObjectContainer.h"
#include "MoveContainer.h"
#include "DrawContainer.h"

GameContext::GameContext(Context* context)
{
	this->context = context;

	moveContainer = new MoveContainer();
	drawContainer = new DrawContainer();
	useContainer = new GameObjectContainer();
	player = new Player(moveContainer, drawContainer,useContainer);
	playerActions.SetPlayer(player);
}

GameContext::~GameContext()
{
	delete player;
	delete levelImporter;
	delete level;
}
