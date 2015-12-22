#pragma once

#include <string>
#include <SFML\Graphics.hpp>

#include "Unit.h"
#include "GameObject.h"

class DrawBehaviour
{
public:
	virtual void Draw(sf::RenderWindow *window, sf::Vector2f viewPortPosition);
	virtual sf::Sprite getCurrentImage();
	GameObject* getGameObject();
	bool isVisible(int screenx, int screeny);
protected:
	int refreshRate;
	GameObject* gameObject;
	sf::Texture unitTexture;
	sf::Sprite unitImage;
};

