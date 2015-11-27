#pragma once
#include "Unit.h"

class RunnerEnemy : public Unit
{
public:
	RunnerEnemy(DrawContainer* container);
	RunnerEnemy(DrawContainer* container, std::string img);
	RunnerEnemy(DrawContainer* container, std::string img, b2Vec2 position, int widht, int height);
	RunnerEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, b2Vec2 position, int widht, int height);

	~RunnerEnemy();
};

