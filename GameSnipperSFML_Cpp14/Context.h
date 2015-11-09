#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

#include "MoveContainer.h"
#include "DrawContainer.h"
#include "MoveBehaviour.h"
#include "DrawBehaviour.h"

#include "Player.h"
#include "PlayerInput.h"
#include "PlayerMovement.h"
#include "KeyMappingImporter.h"
#include "PlayerActions.h"
#include "LevelImporter.h"
#include "Level.h"

class MoveBehaviour;
class DrawBehaviour;
class Unit;

class Context
{
public:
	Context();
	~Context();

	sf::RenderWindow window;

	MoveContainer* moveContainer;
	DrawContainer* drawContainer;

	//std::vector<MoveBehaviour*> allMoveBehaviours;
	std::vector<DrawBehaviour*> allDrawBehaviours;

	std::vector<Unit*> allUnits;
	std::vector<Unit*> getUnits() { return allUnits; };

	Unit* getUnitAt(int i) { return allUnits.at(i); };

	Player* player;
	PlayerInput playerInput;
	PlayerActions playerActions;
	PlayerMovement playerMovement;
	KeyMappingImporter keyMappingImporter;
	
	LevelImporter* l;
	Level* lev;

private:
	int screenWidth = 960;
	int screenHeight = 640;

	sf::Vector2i* screenDimensions;
	sf::Clock clock;
};

