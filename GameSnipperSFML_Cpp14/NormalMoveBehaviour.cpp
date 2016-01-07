#include "stdafx.h"
#include "NormalMoveBehaviour.h"
#include "MoveAction.h"

#include <SFML\System\Vector2.hpp>

NormalMoveBehaviour::NormalMoveBehaviour(GameObject* gameObject)
{
	this->setGameObject(gameObject);

}

NormalMoveBehaviour::~NormalMoveBehaviour()
{
	//Moet ik pointers en float en int ook verwijderen ook destorying die zich zelf. 
}

void NormalMoveBehaviour::Update(sf::Vector2f viewPortPosition)
{
	if (this->checkVisible(viewPortPosition.x, viewPortPosition.y))
	{
		moveAction = new MoveAction{ this->getGameObject(), 0.10f };
		moveAction->Move({ "move-left" });
	}
}
