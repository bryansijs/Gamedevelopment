#include "stdafx.h"
#include "Context.h"

#include "KeyMapping.h"

Context::Context(int screenHeight, int screenWidth)
{
	screenDimensions = { new sf::Vector2i(screenHeight, screenWidth)};
	window.create(sf::VideoMode(screenDimensions->x, screenDimensions->y), "ECHO GAME!!!!");
	window.setKeyRepeatEnabled(false);

	moveContainer = new MoveContainer();
	drawContainer = new DrawContainer();

	player = new Player(moveContainer, drawContainer);
	playerActions.SetPlayer(player);

	l = new LevelImporter(drawContainer);

	l->Import("./Resources/levels/CollideTest.json");
	l->Prepare();
	Level* lev = l->getLevel();

	playerActions.SetContainers(drawContainer, moveContainer, &lev->tiles);


	keyMappingImporter.Import("./Resources/key-mapping.json");
	KeyMapping::ReloadMapping(keyMappingImporter.GetMapping());
}

Context::~Context()
{
	delete(player);
}