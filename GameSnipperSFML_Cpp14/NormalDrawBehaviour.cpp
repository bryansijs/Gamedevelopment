#include "stdafx.h"
#include "NormalDrawBehaviour.h"

#include <iostream>

NormalDrawBehaviour::NormalDrawBehaviour(Unit* u, int refreshRate, std::string playerTextureURL)
{
	this->unit = u;

	if (!unitTexture.loadFromFile(playerTextureURL)) {
		std::cout << "Error could not load player image" << std::endl;
	}
	unitImage.setTexture(unitTexture);
}

NormalDrawBehaviour::NormalDrawBehaviour(Game_Object* game_Object, int refreshRate, std::string objectTextureURL)
{
	this->game_Object = game_Object;

	if (!unitTexture.loadFromFile(objectTextureURL)) {
		std::cout << "Error could not load object image" << std::endl;
	}
	unitImage.setTexture(unitTexture);
}

NormalDrawBehaviour::~NormalDrawBehaviour()
{
}

sf::Sprite NormalDrawBehaviour::getCurrentImage()
{
	if (game_Object != nullptr)
	{
		this->unitImage.setTextureRect(sf::IntRect(
			this->game_Object->get_Image_x(), 
			this->game_Object->get_Image_y(), 
			this->game_Object->width, 
			this->game_Object->height));

		this->unitImage.setPosition(this->game_Object->position);
	}
	else
	{
		this->unitImage.setTextureRect(sf::IntRect(32, 32, 32, 32));
		this->unitImage.setPosition(this->unit->positions);
	}

	return this->unitImage;
}
