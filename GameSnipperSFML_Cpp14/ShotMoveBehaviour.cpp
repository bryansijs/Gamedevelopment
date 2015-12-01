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
		float temp = gameObject->getPosition().y - velocity * Time::deltaTime;
		gameObject->setPosition(gameObject->getPosition().x, temp);
	}
	if (direction == "move-down")
	{
		float temp = gameObject->getPosition().y + velocity * Time::deltaTime;
		gameObject->setPosition(gameObject->getPosition().x, temp);
	}
	if (direction == "move-left")
	{
		float temp = gameObject->getPosition().x - velocity * Time::deltaTime;
		gameObject->setPosition(temp, gameObject->getPosition().y);
	}
	if (direction == "move-right")
	{
		float temp = gameObject->getPosition().x + velocity * Time::deltaTime;
		gameObject->setPosition(temp, gameObject->getPosition().y);
	}
}

bool ShotMoveBehaviour::checkVisible(int screenX, int screenY)
{
	//Wat moet ik doen wanneer ze niet meer visible zijn ook echt verwijderen ????
	//Ik heb de kamer width en height nodig. 
	return true;
}