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
	float speed = velocity * Time::deltaTime;

	if (direction == "move-up")
	{
		gameObject->getBody()->SetLinearVelocity(b2Vec2(0, -speed));
	}
	if (direction == "move-down")
	{
		gameObject->getBody()->SetLinearVelocity(b2Vec2(0, speed));
	}
	if (direction == "move-left")
	{
		gameObject->getBody()->SetLinearVelocity(b2Vec2(-speed, 0));
	}
	if (direction == "move-right")
	{
		gameObject->getBody()->SetLinearVelocity(b2Vec2(speed, 0));
	}
}

bool ShotMoveBehaviour::checkVisible(int screenX, int screenY)
{
	//Wat moet ik doen wanneer ze niet meer visible zijn ook echt verwijderen ????
	//Ik heb de kamer width en height nodig. 
	return true;
}