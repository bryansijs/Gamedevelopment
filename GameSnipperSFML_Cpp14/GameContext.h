#pragma once
#include "Player.h"
#include "LevelImporter.h"
#include "Level.h"
#include "GameActions.h"

class Context;
class MoveContainer;
class DrawContainer;
class GameObjectContainer;

class GameContext
{
public: 
	GameContext(Context* context);
	~GameContext();

	Context* context;

	MoveContainer* moveContainer;
	DrawContainer* drawContainer;
	GameObjectContainer *useContainer;

	Player* player;
	PlayerActions* playerActions;
	GameActions* gameActions;

	LevelImporter* levelImporter;
	Level* level;

	sf::Clock deltaClock;
	sf::Event event;
	sf::View view;
};

