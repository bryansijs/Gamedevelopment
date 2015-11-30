#include "stdafx.h"
#include "ShotMoveBehaviour.h"

#include "Time.h"

ShotMoveBehaviour::ShotMoveBehaviour(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

ShotMoveBehaviour::~ShotMoveBehaviour()
{
}

void ShotMoveBehaviour::Update()
{
	//TODO wat er word hier per direct iets aangepast?
	//position van het object word een private die je later kunt opvragenmet een getter
	//Daarna zul je deze moeten zetten door middel van een setter!
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

void ShotMoveBehaviour::SetDirection(std::string shotDirection)
{
	direction = shotDirection;
}

bool ShotMoveBehaviour::checkVisible(int screenX, int screenY)
{
	//Wat moet ik doen wanneer ze niet meer visible zijn ook echt verwijderen ????
	//Ik heb de kamer width en height nodig. 
	return true;
}