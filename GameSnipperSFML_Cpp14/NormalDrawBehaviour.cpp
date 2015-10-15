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

NormalDrawBehaviour::~NormalDrawBehaviour()
{
}

sf::Sprite NormalDrawBehaviour::getCurrentImage()
{
	this->unitImage.setTextureRect(sf::IntRect(32, 32, 32, 32));

	this->unitImage.setPosition(this->unit->positions);
	return this->unitImage;
}
