#pragma once
#include "DrawBehaviour.h"

class PlayerDrawBehaviour : public DrawBehaviour
{
public:
	PlayerDrawBehaviour(GameObject* gameObject, int refreshRate, std::string textureUrl);
	~PlayerDrawBehaviour();

	void Draw(sf::RenderWindow *window) override;
	sf::Sprite getCurrentImage();
};

