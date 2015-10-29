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
		this->gameObject->get_Image_x(),
		this->gameObject->get_Image_y(),
		this->gameObject->width,
		this->gameObject->height));

	this->unitImage.setPosition(this->gameObject->position);

	/*this->unitImage.setTextureRect(sf::IntRect(0, 0, 32, 32));
	this->unitImage.setPosition(this->gameObject->position);*/

	return this->unitImage;
}