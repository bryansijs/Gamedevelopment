#pragma once
#include "BaseEnemy.h"

class BasicEnemy : public BaseEnemy
{
public:
	BasicEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer,std::map<std::string, std::string>& properties,b2World* world);
	~BasicEnemy();
};

