#pragma once
#include "Player.h"
#include "PlayerInput.h"
#include "LevelImporter.h"
#include "Level.h"
#include "GameInput.h"

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

	PlayerInput playerInput = PlayerInput(this);
	GameInput gameInput = GameInput(this);

	LevelImporter* levelImporter;
	Level* level;

	sf::Clock deltaClock;
	sf::Event event;
	sf::View view;
};

