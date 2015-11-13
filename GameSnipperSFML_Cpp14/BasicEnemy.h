#pragma once
#include "Unit.h"


class BasicEnemy : public Unit
{
public:
	BasicEnemy::BasicEnemy(DrawContainer* container);
	BasicEnemy::BasicEnemy(DrawContainer* container, std::string img);
	BasicEnemy::BasicEnemy(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height);
	BasicEnemy::BasicEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, sf::Vector2f position, int widht, int height);

	~BasicEnemy();
};

