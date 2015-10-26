#pragma once
#include <string>
#include "Unit.h"
#include "Game_Object.h"

class DrawBehaviour
{
public:
	virtual sf::Sprite getCurrentImage();
	Unit* getUnit();
	Game_Object* getObject();

protected:
	int refreshRate;
	Unit* unit;
	Game_Object* game_Object;
	sf::Texture unitTexture;
	sf::Sprite unitImage;
};

