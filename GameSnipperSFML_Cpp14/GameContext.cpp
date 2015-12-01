#include "stdafx.h"
#include "GameContext.h"
#include "GameObjectContainer.h"
#include "MoveContainer.h"
#include "DrawContainer.h"
#include "KeyMapping.h"




GameContext::GameContext(Context* context)
{
	this->context = context;

	moveContainer = new MoveContainer();
	drawContainer = new DrawContainer();
	useContainer = new GameObjectContainer();
	player = new Player(moveContainer, drawContainer, useContainer);
	playerActions.SetPlayer(player);

	sfx.loadFromFile("./Resources/sfx/confirm.ogg");
	pauseSound.setBuffer(sfx);

	keyMappingImporter.Import("./Resources/key-mapping.json");
	KeyMapping::ReloadMapping(keyMappingImporter.GetMapping());


	font.loadFromFile("./Resources/arial.ttf");
	// Create a text
	pauzeText = sf::Text("PAUZE", font);
	pauzeText.setCharacterSize(100);
	pauzeText.setStyle(sf::Text::Bold);
	pauzeText.setColor(sf::Color::Red);
	pauzeText.setPosition(20, 20);
}

GameContext::~GameContext()
{
	delete player;
	delete levelImporter;
	delete level;
}
