#pragma once
#include <vector>

class MoveBehaviour;
class DrawBehaviour;
class UnitState;

class Unit
{
public:
	int id;
	enum direction { UP, RIGHT, DOWN, LEFT };

	UnitState* currentState;
	MoveBehaviour* moveBehaviour;
	DrawBehaviour* drawBehaviour;

	std::vector<MoveBehaviour*>* allMoveBehaviours;
	std::vector<DrawBehaviour*>* allDrawBehaviours;
	std::vector<Unit*>* allUnits;

	void setCurrentState(UnitState* state);
	void setMoveBehaviour(MoveBehaviour* newMoveBehaviour);
	void setDrawBehaviour(DrawBehaviour* newDrawBehaviour);
};

