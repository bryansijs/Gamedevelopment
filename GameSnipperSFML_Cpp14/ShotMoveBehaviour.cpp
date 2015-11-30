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
		float temp = gameObject->getBody()->GetPosition().y - velocity * Time::deltaTime;
		gameObject->setPosition(gameObject->getBody()->GetPosition().x, temp);
	}
	if (direction == "move-down")
	{
		float temp = gameObject->getBody()->GetPosition().y + velocity * Time::deltaTime;
		gameObject->setPosition(gameObject->getBody()->GetPosition().x, temp);
	}
	if (direction == "move-left")
	{

		float temp = gameObject->getBody()->GetPosition().x - velocity * Time::deltaTime;
		gameObject->setPosition(temp, gameObject->getBody()->GetPosition().y);

}
	if (direction == "move-right")
	{
		float temp = gameObject->getBody()->GetPosition().x + velocity * Time::deltaTime;
		gameObject->setPosition(temp, gameObject->getBody()->GetPosition().y);

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