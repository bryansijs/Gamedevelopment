#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Unit.h"

class DrawBehaviour
{
public:
	virtual void getCurrentImage();
	Unit* getUnit();

protected:
	int refreshRate;
	Unit* unit;
	sf::Texture unitTexture;
	sf::Sprite unitImage;
};

