#include "stdafx.h"
#include "ShotMoveBehaviour.h"

#include "Time.h"

ShotMoveBehaviour::ShotMoveBehaviour(GameObject* gameObject, std::string shotDirection)
{
	this->gameObject = gameObject;
	direction = shotDirection;
}

ShotMoveBehaviour::~ShotMoveBehaviour()
{
}

void ShotMoveBehaviour::Update(sf::Vector2f viewPortPosition)
{
	if (direction == "move-up")
	{
		float temp = gameObject->getPositionY() - velocity * Time::deltaTime;
		gameObject->setPosition(sf::Vector2f(gameObject->getPositionX(), temp));
	}
	if (direction == "move-down")
	{
		float temp = gameObject->getPositionY() + velocity * Time::deltaTime;
		gameObject->setPosition(sf::Vector2f(gameObject->getPositionX(), temp));
	}
	if (direction == "move-left")
	{
		float temp = gameObject->getPositionX() - velocity * Time::deltaTime;
		gameObject->setPosition(sf::Vector2f(temp, gameObject->getPositionY()));
	}
	if (direction == "move-right")
	{
		float temp = gameObject->getPositionX() + velocity * Time::deltaTime;
		gameObject->setPosition(sf::Vector2f(temp, gameObject->getPositionY()));
	}
}

bool ShotMoveBehaviour::checkVisible(int screenX, int screenY)
{
	//Wat moet ik doen wanneer ze niet meer visible zijn ook echt verwijderen ????
	//Ik heb de kamer width en height nodig. 
	return true;
}