#include "stdafx.h"
#include "Context.h"

#include "KeyMapping.h"

Context::Context(int screenHeight, int screenWidth)
{
	screenDimensions = { new sf::Vector2i(screenHeight, screenWidth)};
	window.create(sf::VideoMode(screenDimensions->x, screenDimensions->y), "ECHO GAME!!!!");
	window.setKeyRepeatEnabled(false);

	player = new Player();
	playerActions.SetPlayer(player);
	allDrawBehaviours.push_back(player->drawBehaviour);

	keyMappingImporter.Import("./Resources/key-mapping.json");
	KeyMapping::ReloadMapping(keyMappingImporter.GetMapping());
}

Context::~Context()
{
	delete(player);
}

