#pragma once
#include <vector>

#include "GameObject.h"

class MoveContainer;
class DrawContainer;
class MoveBehaviour;
class DrawBehaviour;
class UnitState;

class Unit : public GameObject
{
public:
	UnitState* currentState;

	void setCurrentState(UnitState* state);
};

