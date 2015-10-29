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
	if (direction == "move-up")
	{
		gameObject->position.y += -velocity * Time::deltaTime;
	}
	if (direction == "move-down")
	{
		gameObject->position.y += velocity * Time::deltaTime;
	}
	if (direction == "move-left")
	{
		gameObject->position.x += -velocity * Time::deltaTime;
	}
	if (direction == "move-right")
	{
		gameObject->position.x += velocity * Time::deltaTime;
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