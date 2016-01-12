#pragma once
#include "BaseEnemy.h"

class RunnerEnemy : public BaseEnemy
{
public:

	RunnerEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, b2World* world);
	void setPattern();

	~RunnerEnemy();
};

