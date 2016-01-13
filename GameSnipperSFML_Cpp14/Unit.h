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
	int health = 100;
	int maxHealth = 100;
	bool isVisible = true;
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

	void setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; }
	int getMaxHealth() { return maxHealth; }
	void Damage(int amount);

	void setVisible(bool visible) { this->isVisible = visible;}
	bool getVisible() { return this->isVisible; }
};

