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
private:
	int health;
public:
	UnitState* currentState;
	Unit::Unit(DrawContainer* dContainer, std::string img);
	Unit::Unit(DrawContainer* dContainer, std::string img, MoveContainer* mContainer);
	Unit::Unit(DrawContainer* dContainer, std::string img, GameObjectContainer* goContainer);
	Unit::Unit(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* goContainer);
	Unit::Unit();
	Unit::Unit(DrawContainer* container);
	void setCurrentState(UnitState* state);
	void setHealth(int health) { this->health = health; }
	int getHealth() { return health; }
};

