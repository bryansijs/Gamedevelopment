#include "stdafx.h"
#include "ShotMoveBehaviour.h"
#include "Bullet.h";
#include "Time.h"

ShotMoveBehaviour::ShotMoveBehaviour(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

ShotMoveBehaviour::ShotMoveBehaviour(GameObject* gameObject, std::string shotDirection)
{
	this->setGameObject(gameObject);
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
		this->getGameObject()->getBody()->SetLinearVelocity(b2Vec2(0, -speed));
	}
	if (direction == "move-down")
	{
		this->getGameObject()->getBody()->SetLinearVelocity(b2Vec2(0, speed));
	}
	if (direction == "move-left")
	{
		this->getGameObject()->getBody()->SetLinearVelocity(b2Vec2(-speed, 0));
	}
	if (direction == "move-right")
	{
		this->getGameObject()->getBody()->SetLinearVelocity(b2Vec2(speed, 0));
	}


}

void ShotMoveBehaviour::SetDirection(std::string direction)
{
	this->direction = direction;
}
