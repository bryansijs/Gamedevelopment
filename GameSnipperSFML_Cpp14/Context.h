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

class MoveBehaviour;
class DrawBehaviour;
class Unit;

class Context
{
public:
	Context(int screenHeight, int screenWidth);
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
private:
	sf::Vector2i* screenDimensions;
	sf::Clock clock;
};

