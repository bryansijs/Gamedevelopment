#include "stdafx.h"
#include "MoveAction.h"

#include "GameObject.h"
#include "Time.h"
#include "Tile.h"

#include <math.h>
#include <iostream>

MoveAction::MoveAction()
{
}

MoveAction::~MoveAction()
{
}

void MoveAction::Move(std::vector<std::string> directions, GameObject *gameObject, std::vector<Tile*>* tiles)
{
	this->directions = directions;
	this->gameObject = gameObject;
	this->tiles = tiles;

	Move();
}

void MoveAction::Move(std::vector<std::string> directions, GameObject *gameObject)
{
	this->directions = directions;
	this->gameObject = gameObject;

	Move();
}

void MoveAction::Move()
{
	for (std::vector<std::string>::iterator it = directions.begin(); it != directions.end(); ++it)
	{
		if (*it == "move-up")
		{
			gameObject->setImageY(3);
			velocity.y -= speed;
		}
		if (*it == "move-down")
		{
			gameObject->setImageY(0);
			velocity.y += speed;
		}
		if (*it == "move-left")
		{
			gameObject->setImageY(1);
			velocity.x -= speed;
		}
		if (*it == "move-right")
		{
			gameObject->setImageY(2);
			velocity.x += speed;
		}
	}

	velocity *= Time::deltaTime;

	if (directions.size() == 2)
	{
		velocity.x *= cos(45 * 3.14159265359 / 180);
		velocity.y *= sin(45 * 3.14159265359 / 180);
	}

	if (tiles != nullptr)
	{
		if (gameObject->isColliding(*tiles, velocity))
		{
			return;
		}
	}

	velocity.x = roundf(velocity.x * 100) / 100;
	velocity.y = roundf(velocity.y * 100) / 100;

	AnimateMovement(gameObject);

	gameObject->setPosition(gameObject->getPosition() + velocity);
}

void MoveAction::AnimateMovement(GameObject *gameObject)
{
	if (animationDelay > 0)
	{
		animationDelay = animationDelay - Time::deltaTime;
		return;
	}

	if (animateState == animationStates)
		animateState = 0;

	gameObject->setImageX(animateState);
	animateState++;
	animationDelay = 0.05;
}

void MoveAction::AnimateMovement(GameObject* gameObject, int state)
{
	animateState = state;
	AnimateMovement(gameObject);
}

void MoveAction::SetAnimationStates(int states)
{
	animationStates = states;
}
