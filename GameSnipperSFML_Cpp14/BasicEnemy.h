#pragma once
#include "Unit.h"


class BasicEnemy : public Unit
{
public:
	BasicEnemy(DrawContainer* container);
	BasicEnemy(DrawContainer* container, std::string img);
	BasicEnemy(DrawContainer* container, std::string img, b2Vec2 position, int widht, int height);
	BasicEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer,GameObjectContainer* gameObjectContainer, b2Vec2 position, int widht, int height);

	~BasicEnemy();
};

