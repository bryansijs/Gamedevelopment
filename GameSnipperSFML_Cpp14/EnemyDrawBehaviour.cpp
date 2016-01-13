#include "stdafx.h"
#include "EnemyDrawBehaviour.h"


#include "BaseEnemy.h"
#include <iostream>

EnemyDrawBehaviour::EnemyDrawBehaviour(GameObject* gameObject, int refreshRate, std::string textureUrl)
{
	this->gameObject = gameObject;

	if (!unitTexture.loadFromFile(textureUrl)) {
		std::cout << "Error could not load player image" << std::endl;
	}
	unitImage.setTexture(unitTexture);
}

EnemyDrawBehaviour::~EnemyDrawBehaviour()
{
}

void EnemyDrawBehaviour::Draw(sf::RenderWindow *window, sf::Vector2f viewPortPosition)
{
	/*if (dynamic_cast<BaseEnemy*>(this->gameObject)->getVisible())
	{*/
		window->draw(getCurrentImage());
		window->draw(dynamic_cast<BaseEnemy*>(this->gameObject)->getLineOfSightConvex());
		window->draw(dynamic_cast<BaseEnemy*>(this->gameObject)->getMaxHpBar());
		window->draw(dynamic_cast<BaseEnemy*>(this->gameObject)->getHpBar());
	//}
}

sf::Sprite EnemyDrawBehaviour::getCurrentImage()
{
	this->unitImage.setTextureRect(sf::IntRect(
		this->gameObject->getImageX(),
		this->gameObject->getImageY(),
		this->gameObject->getWidth(),
		this->gameObject->getHeight()));

	this->unitImage.setPosition(sf::Vector2f(gameObject->getBody()->GetPosition().x, gameObject->getBody()->GetPosition().y));

	return this->unitImage;
}

