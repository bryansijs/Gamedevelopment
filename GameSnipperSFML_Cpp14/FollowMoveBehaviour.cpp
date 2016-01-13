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

	//dynamic_cast<BaseEnemy*>(gameObject)->setVisible(this->checkVisible(viewPortPosition.x, viewPortPosition.y));

	/*if (dynamic_cast<BaseEnemy*>(gameObject)->getVisible())
	{*/
		this->setDirection();
	//}

	moveAction->Move(this->getDirection());
}

void FollowMoveBehaviour::setDirection()
{
	float x = 0, y = 0, x2 = 0, y2 = 0;

	//enemy position
	x = gameObject->getBody()->GetPosition().x;
	y = gameObject->getBody()->GetPosition().y;

	//target "player" position
	x2 = dynamic_cast<BaseEnemy*>(gameObject)->getTarget()->getBody()->GetPosition().x;
	y2 = dynamic_cast<BaseEnemy*>(gameObject)->getTarget()->getBody()->GetPosition().y;

	if ((x - x2) > 5 && (y - y2) > 5 || (x - x2) > 5 && (y - y2) < -5 || (x - x2) < -5 && (y - y2) > 5 || (x - x2) < -5 && (y - y2) < -5)
	{
		if ((x - x2) > 5 && (y - y2) > 5)
		{
			if ((x - x2) - (y - y2) > 0)
				this->setShotDirection("move-left");
			else
				this->setShotDirection("move-up");
			mDircection = "move-upleft";
		}
		else if ((x - x2) > 5 && (y - y2) < -5)
		{
			if ((x - x2) + (y - y2) > 0)
				this->setShotDirection("move-left");
			else
				this->setShotDirection("move-down");
			mDircection = "move-downleft";
		}
		else if ((x - x2) < -5 && (y - y2) > 5)
		{
			if ((x - x2) + (y - y2) > 0)
				this->setShotDirection("move-up");
			else
				this->setShotDirection("move-right");
			mDircection = "move-upright";
		}
		else if ((x - x2) < -5 && (y - y2) < -5)
		{
			if ((x - x2) - (y - y2) > 0)
				this->setShotDirection("move-down");
			else
				this->setShotDirection("move-right");
			mDircection = "move-downright";
		}
	}
	else
	{
		if ((x - x2) >= 5)
		{
			mDircection = "move-left";
		}
		else if ((x - x2) <= -5)
		{
			mDircection = "move-right";
		}
		else if ((y - y2) >= 5)
		{
			mDircection = "move-up";
		}
		else if ((y - y2) <= -5)
		{
			mDircection = "move-down";
		}
	}

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
