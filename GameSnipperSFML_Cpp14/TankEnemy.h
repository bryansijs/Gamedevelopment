#pragma once
#include "Unit.h"

class TankEnemy : public Unit
{
public:

	TankEnemy(DrawContainer* container);
	TankEnemy(DrawContainer* container, std::string img);
	TankEnemy(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height);
	TankEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, sf::Vector2f position, int widht, int height);

	~TankEnemy();
};

