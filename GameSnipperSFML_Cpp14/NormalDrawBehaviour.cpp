#include "stdafx.h"
#include "NormalDrawBehaviour.h"
#include "BaseEnemy.h"
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
	if (dynamic_cast<BaseEnemy*>(this->gameObject))
	{
		window->draw(dynamic_cast<BaseEnemy*>(this->gameObject)->getConvex());
	}
}

sf::Sprite NormalDrawBehaviour::getCurrentImage()
{
	this->unitImage.setTextureRect(sf::IntRect(
		this->gameObject->getImageX(),
		this->gameObject->getImageY(),
		this->gameObject->getWidth(),
		this->gameObject->getHeight()));

	this->unitImage.setPosition(sf::Vector2f(gameObject->getBody()->GetPosition().x, gameObject->getBody()->GetPosition().y));

	return this->unitImage;
}
