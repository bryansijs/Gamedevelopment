#pragma once
#include "Unit.h"


class BasicEnemy : public Unit
{
public:
	BasicEnemy(DrawContainer* container);
	BasicEnemy(DrawContainer* container, std::string img);
	BasicEnemy(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height);
	BasicEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer,GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height);

	~BasicEnemy();
};

