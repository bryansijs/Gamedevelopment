#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

class MoveBehaviour;
class DrawBehaviour;
class UnitState;

class Unit
{
public:
	int id;
	enum direction {Down, Left, Right, Up};
	sf::Vector2f positions;

	UnitState* currentState;
	MoveBehaviour* moveBehaviour;
	DrawBehaviour* drawBehaviour;

	std::vector<MoveBehaviour*>* allMoveBehaviours;
	std::vector<DrawBehaviour*>* allDrawBehaviours;
	std::vector<Unit*>* allUnits;

	void setCurrentState(UnitState* state);
	void setMoveBehaviour(MoveBehaviour* newMoveBehaviour);
	void setDrawBehaviour(DrawBehaviour* newDrawBehaviour);

	void setPosition(float x, float y) { positions.x = x; positions.y = y; };
};

