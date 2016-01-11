#include "stdafx.h"
#include "FollowMoveBehaviour.h"
#include "Tile.h"
#include "Time.h"
#include "BaseEnemy.h"
#include <cstdlib>

FollowMoveBehaviour::FollowMoveBehaviour(GameObject* gameObject)
{
	this->setGameObject(gameObject);
	moveAction = new MoveAction{ gameObject, 0.10f };
}

FollowMoveBehaviour::~FollowMoveBehaviour()
{
}

void FollowMoveBehaviour::Update(sf::Vector2f viewPortPosition)
{
	if (this->getGameObject()->isFlaggedForDelete)return;

	if (this->checkVisible(viewPortPosition.x, viewPortPosition.y))
	{
		this->setDirection();
	}
}

void FollowMoveBehaviour::setDirection()
{
	//get player direction and set to that direction.

	finalizeDirection();
}

void FollowMoveBehaviour::finalizeDirection()
{
	this->clearDirection();
	if (mDircection == "move-upleft")
	{
		this->addDirection("move-up");
		this->addDirection("move-left");
		return;
	}
	if (mDircection == "move-upright")
	{
		this->addDirection("move-up");
		this->addDirection("move-right");
		return;
	}
	if (mDircection == "move-downleft")
	{
		this->addDirection("move-down");
		this->addDirection("move-left");
		return;
	}
	if (mDircection == "move-downright")
	{
		this->addDirection("move-down");
		this->addDirection("move-right");
		return;
	}

	this->addDirection(mDircection);
}
