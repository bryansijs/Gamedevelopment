#pragma once
#include "BaseEnemy.h"

class TankEnemy : public BaseEnemy
{
public:

	TankEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, b2World* world);


	~TankEnemy();
};

