#pragma once
#include "BaseEnemy.h"

class TankEnemy : public BaseEnemy
{
public:

	TankEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height);
	TankEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties);

	~TankEnemy();
};

