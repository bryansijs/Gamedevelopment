#pragma once
#include "DrawBehaviour.h"

class EnemyDrawBehaviour : public DrawBehaviour
{
public:
	EnemyDrawBehaviour(GameObject* gameObject, int refreshRate, std::string textureURL);
	~EnemyDrawBehaviour();

	void Draw(sf::RenderWindow *window, sf::Vector2f viewPortPosition) override;
	sf::Sprite getCurrentImage();
};

