#include "stdafx.h"
#include "WanderMoveBehaviour.h"
#include "Tile.h"
#include "Random.h"
#include "Time.h"
#include "BaseEnemy.h"
#include <cstdlib>
WanderMoveBehaviour::WanderMoveBehaviour(GameObject* gameObject)
{
	this->gameObject = gameObject;
	moveAction = new MoveAction{ gameObject, 0.10f };

	moveDistance = 0;

	std::vector<std::string> dir =
	{
		{ "move-up" },
		{ "move-down" },
		{ "move-left" },
		{ "move-right" },
		{ "move-upright" },
		{ "move-downright" },
		{ "move-upleft" },
		{ "move-downleft" },
		{ "move-not" }
	};

	this->swapDirections(dir);
	dir.clear();

	if (dynamic_cast<BaseEnemy*>(gameObject)){
		this->maxMoveDistance = dynamic_cast<BaseEnemy*>(gameObject)->getMaxWanderDistance();
		this->minMoveDistance = dynamic_cast<BaseEnemy*>(gameObject)->getMinWanderDistance();
		this->defaultMoveDistance = dynamic_cast<BaseEnemy*>(gameObject)->getDefaultWanderDistance();
	}
}

WanderMoveBehaviour::~WanderMoveBehaviour()
{
}

void WanderMoveBehaviour::Update(sf::Vector2f viewPortPosition)
{
	if (checkVisible(viewPortPosition.x, viewPortPosition.y))
	{

		if (currentMoveDistance >= moveDistance)
		{
			this->setDirection();
		}

		for (b2ContactEdge* ce = this->gameObject->getBody()->GetContactList(); ce; ce = ce->next){
			b2Contact* c = ce->contact;
			GameObject* obj = static_cast<GameObject*>(ce->other->GetUserData());
			

			b2Fixture* fixtureA = ce->contact->GetFixtureA();
			b2Fixture* fixtureB = ce->contact->GetFixtureB();

			if (fixtureA->IsSensor()|| fixtureB->IsSensor())continue;


			if (dynamic_cast<BaseEnemy*>(obj))
			{
				this->MoveAway(dynamic_cast<BaseEnemy*>(obj));
			}
			if (dynamic_cast<Tile*>(obj))
				{
					if (c->IsTouching()) {
						this->setDirection();
					}
				}
				
		}


		moveAction->Move(this->getDirection());
		currentMoveDistance += 100.0f* Time::deltaTime;

		if (mDircection == "move-not")
			currentMoveDistance += 360.0f* Time::deltaTime;

		reverseTime += 100.0f * Time::deltaTime;

	}


}

bool WanderMoveBehaviour::checkVisible(int screenX, int screenY)
{
	return (gameObject->getPosition().x > screenX && gameObject->getPosition().x < screenX + 960 && gameObject->getPosition().y > screenY && gameObject->getPosition().y < screenY + 640);
}


void WanderMoveBehaviour::MoveAway(BaseEnemy* obj)
{
	if (this->getDirection() == obj->getMoveBehaviour()->getDirection())
	{
		this->setDirection();
	}
	else
		this->reverseDirection();


}


void WanderMoveBehaviour::finalizeDirection()
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

	moveDistance = Random::Number(minMoveDistance, maxMoveDistance) + defaultMoveDistance;
	currentMoveDistance = 0;
}

void WanderMoveBehaviour::reverseDirection()
{

	if (reverseTime < reversecoolDown)return;

	reverseTime = 0;

	if (mDircection.find("up") != std::string::npos)
		Replace(mDircection, "up", "down");
	else
		Replace(mDircection, "down", "up");

	if (mDircection.find("left") != std::string::npos)
		Replace(mDircection, "left", "right");
	else
		Replace(mDircection, "right", "left");


	finalizeDirection();

}

void WanderMoveBehaviour::setDirection()
{

	std::string oldDirection = mDircection;
	mDircection = getDirection(Random::Number(0, getDirectionSize() - 1));

	while (mDircection == oldDirection) {
		mDircection = getDirection(Random::Number(0, getDirectionSize() - 1));
	}

	finalizeDirection();



}

