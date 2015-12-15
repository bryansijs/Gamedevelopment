#include "stdafx.h"
#include "MoveAction.h"

#include "GameObject.h"
#include "Time.h"
#include "Animation.h"

#include <math.h>
#include <iostream>

MoveAction::MoveAction(GameObject *gameObject, float delay)
{
	this->gameObject = gameObject;
	animation = new Animation(gameObject, delay, 1);
}

MoveAction::~MoveAction()
{
}

void MoveAction::Move(std::vector<std::string> directions)
{
	this->directions = directions;

	Move();
}

void MoveAction::Reset()
{
	animation->Reset();
	gameObject->getBody()->SetLinearVelocity(b2Vec2(0, 0));
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

	velocity.x = roundf(velocity.x * 100) / 100;
	velocity.y = roundf(velocity.y * 100) / 100;

	if(velocity.x != 0 || velocity.y != 0)
		animation->Animate();

	gameObject->getBody()->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}