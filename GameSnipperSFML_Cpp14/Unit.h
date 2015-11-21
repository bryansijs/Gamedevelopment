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
	Unit::Unit(DrawContainer* dContainer, std::string img);
	Unit::Unit(DrawContainer* dContainer, std::string img, MoveContainer* mContainer);
	Unit::Unit();
	Unit::Unit(DrawContainer* container);
	void setCurrentState(UnitState* state);
};

