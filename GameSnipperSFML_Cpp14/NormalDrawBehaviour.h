#pragma once
#include "DrawBehaviour.h"

class NormalDrawBehaviour : public DrawBehaviour
{
public:
	NormalDrawBehaviour(GameObject* gameObject, int refreshRate, std::string textureURL);
	~NormalDrawBehaviour();

	void Draw(sf::RenderWindow *window) override;
	sf::Sprite getCurrentImage();
};

