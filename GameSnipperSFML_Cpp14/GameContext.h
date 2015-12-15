#pragma once
#include "SFML/Graphics.hpp"
#include "Context.h"
#include "Player.h"
#include "LevelImporter.h"
#include "Level.h"
#include "PauseMenu.h"
#include "FPSShow.h"

class Context;
class MoveContainer;
class DrawContainer;
class GameObjectContainer;
class CollisionListener;
class PauzeMenu;

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

	void setMenuPosition();
	PauseMenu* pauze = new PauseMenu{ 321,395 };

	FPSShow* fpsShow = new FPSShow{};

	b2World* world;
	CollisionListener* collisionListener;
};

