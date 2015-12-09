#include "stdafx.h"
#include "PlayerDrawBehaviour.h"

PlayerDrawBehaviour::PlayerDrawBehaviour(GameObject* gameObject, int refreshRate, std::string textureUrl)
{
	this->gameObject = gameObject;

	if (!unitTexture.loadFromFile("./Resources/sprites/" + textureUrl)) {
		std::cout << "Error could not load player image" << std::endl;
	}
	unitImage.setTexture(unitTexture);
}

PlayerDrawBehaviour::~PlayerDrawBehaviour()
{
}

void PlayerDrawBehaviour::Draw(sf::RenderWindow *window)
{
	window->draw(getCurrentImage());
}

sf::Sprite PlayerDrawBehaviour::getCurrentImage()
{
	this->unitImage.setTextureRect(sf::IntRect(
		this->gameObject->getImageX(),
		this->gameObject->getImageY(),
		this->gameObject->getWidth(),
		this->gameObject->getHeight()));

	this->unitImage.setPosition(sf::Vector2f(this->gameObject->getBody()->GetPosition().x, this->gameObject->getBody()->GetPosition().y));

	return this->unitImage;
}