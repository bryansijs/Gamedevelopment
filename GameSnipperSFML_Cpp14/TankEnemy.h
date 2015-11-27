#pragma once
#include "Unit.h"

class TankEnemy : public Unit
{
public:

	TankEnemy(DrawContainer* container);
	TankEnemy(DrawContainer* container, std::string img);
	TankEnemy(DrawContainer* container, std::string img, b2Vec2 position, int widht, int height);
	TankEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, b2Vec2 position, int widht, int height);

	~TankEnemy();
};

