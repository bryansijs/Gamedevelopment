#pragma once

#include <string>
#include <SFML\Graphics.hpp>

#include "Unit.h"
#include "GameObject.h"

class DrawBehaviour
{
public:
	virtual void Draw(sf::RenderWindow *window);
	virtual sf::Sprite getCurrentImage();
	GameObject* getGameObject();

protected:
	int refreshRate;
	GameObject* gameObject;
	sf::Texture unitTexture;
	sf::Sprite unitImage;
};

