#include "stdafx.h"
#include "Context.h"
#include "Unit.h"
#include "MoveBehaviour.h"
#include "DrawBehaviour.h"
#include "Player.h"
#include "KeyMapping.h"

Context::Context(int screenHeight, int screenWidth)
{
	screenDimensions = { new sf::Vector2i(screenHeight, screenWidth)};
	window.create(sf::VideoMode(screenDimensions->x, screenDimensions->y), "ECHO GAME!!!!");
	window.setKeyRepeatEnabled(false);

	player = new Player();
	playerMovement.SetPlayer(player);

	keyMappingImporter.Import("./Resources/key-mapping.json");
	KeyMapping::ReloadMapping(keyMappingImporter.GetMapping());
}

Context::~Context()
{
	delete(player);
}

