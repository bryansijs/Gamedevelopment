#include "stdafx.h"
#include "NormalDrawBehaviour.h"

#include <iostream>

NormalDrawBehaviour::NormalDrawBehaviour(GameObject* gameObject, int refreshRate, std::string textureUrl)
{
	this->gameObject = gameObject;

	if (!unitTexture.loadFromFile(textureUrl)) {
		std::cout << "Error could not load player image" << std::endl;
	}
	unitImage.setTexture(unitTexture);
}

NormalDrawBehaviour::~NormalDrawBehaviour()
{
}

void NormalDrawBehaviour::Draw(sf::RenderWindow *window)
{
	window->draw(getCurrentImage());
}

sf::Sprite NormalDrawBehaviour::getCurrentImage()
{
	this->unitImage.setTextureRect(sf::IntRect(
		this->gameObject->getImageX(),
		this->gameObject->getImageY(),
		this->gameObject->getWidth(),
		this->gameObject->getHeight()));

	this->unitImage.setPosition(this->gameObject->getPosition());

	return this->unitImage;
}
