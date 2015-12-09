#include "stdafx.h"
#include "NormalMoveBehaviour.h"

#include "MoveAction.h"
#include "Level.h"

#include <SFML\System\Vector2.hpp>

NormalMoveBehaviour::NormalMoveBehaviour(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

NormalMoveBehaviour::~NormalMoveBehaviour()
{
	//Moet ik pointers en float en int ook verwijderen ook destorying die zich zelf. 
}

void NormalMoveBehaviour::Update(sf::Vector2f viewPortPosition)
{
	if (checkVisible(viewPortPosition.x, viewPortPosition.y))
	{
		moveAction = new MoveAction{ gameObject, 0.10f };
		moveAction->Move({ "move-left" });
	}
}

bool NormalMoveBehaviour::checkVisible(int screenX, int screenY)
{
	if (gameObject->getPosition().x > screenX && gameObject->getPosition().x < screenX + 960 && gameObject->getPosition().y > screenY && gameObject->getPosition().y < screenY + 640)
	{
		return true;
	}
	
	return false;
}
