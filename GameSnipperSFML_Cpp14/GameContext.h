#pragma once

#include "Player.h"
#include "PlayerInput.h"
#include "PlayerActions.h"
#include "PlayerMovement.h"
#include "KeyMappingImporter.h"

#include "LevelImporter.h"
#include "Level.h"

class Context;
class MoveContainer;
class DrawContainer;

class GameContext
{
public:
	GameContext(Context* context);
	~GameContext();

	Context* context;

	MoveContainer* moveContainer;
	DrawContainer* drawContainer;

	Player* player;
	PlayerInput playerInput;
	PlayerActions playerActions;
	PlayerMovement playerMovement;
	KeyMappingImporter keyMappingImporter;

	LevelImporter* levelImporter;
	Level* level;

	sf::Clock deltaClock;
	sf::Event event;
	sf::View view;
};

