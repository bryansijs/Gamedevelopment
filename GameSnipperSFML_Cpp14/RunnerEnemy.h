#pragma once
#include "BaseEnemy.h"

class RunnerEnemy : public BaseEnemy
{
public:

	RunnerEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height);
	RunnerEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties);

	~RunnerEnemy();
};

