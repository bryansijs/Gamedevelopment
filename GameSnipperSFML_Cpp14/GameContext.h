#pragma once

#include "Context.h"

#include "Player.h"

#include "Player.h"
#include "LevelImporter.h"
#include "Level.h"

class MoveContainer;
class DrawContainer;
class GameObjectContainer;
class CollisionListener;

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

	LevelImporter* levelImporter;
	Level* level;

	sf::Clock deltaClock;
	sf::Event event;
	sf::View view;
	b2World* world;
	CollisionListener* collisionListener;
};

