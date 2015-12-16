#include "stdafx.h"
#include "WanderMoveBehaviour.h"
#include "Tile.h"
#include "Random.h"

#include <cstdlib>

WanderMoveBehaviour::WanderMoveBehaviour(GameObject* gameObject)
{
	this->gameObject = gameObject;
	moveAction = new MoveAction{ gameObject, 0.10f };
	startPosition = gameObject->getPosition();
	endPosition = gameObject->getPosition();
}

WanderMoveBehaviour::~WanderMoveBehaviour()
{
}

void WanderMoveBehaviour::Update(sf::Vector2f viewPortPosition)
{
	if (checkVisible(viewPortPosition.x, viewPortPosition.y))
	{
		if (startPosition == endPosition || std::abs(gameObject->getPosition().x - startPosition.x) > moveDistance || std::abs(gameObject->getPosition().y - startPosition.y) > moveDistance)
		{
			startPosition = gameObject->getPosition();

			moveDistance = Random::Number(minMoveDistance, maxMoveDistance) + defaultMoveDistance;
			this->direction = directions[Random::Number(0, directions.size() - 1)];
		}

		for (b2ContactEdge* ce = this->gameObject->getBody()->GetContactList(); ce; ce = ce->next)
		{
			b2Contact* c = ce->contact;

			GameObject* obj = static_cast<GameObject*>(ce->other->GetUserData());
			if (dynamic_cast<Tile*>(obj))
			{
				if (c->IsTouching())
					this->setDirection();
			}
		}

		moveAction->Move({ this->direction });
	}
}

bool WanderMoveBehaviour::checkVisible(int screenX, int screenY)
{
	return (gameObject->getPosition().x > screenX && gameObject->getPosition().x < screenX + 960 && gameObject->getPosition().y > screenY && gameObject->getPosition().y < screenY + 640);
}



void WanderMoveBehaviour::setDirection()
{

	if (direction == "move-up") {
		direction = "move-down";
		this->gameObject->setPosition(this->gameObject->getBody()->GetPosition().x, this->gameObject->getBody()->GetPosition().y + 5);
		this->gameObject->getBody()->SetTransform(b2Vec2(this->gameObject->getBody()->GetPosition().x, this->gameObject->getBody()->GetPosition().y + 5), 0);

	}
	else if (direction == "move-down")
	{

		direction = "move-up";
		this->gameObject->setPosition(this->gameObject->getBody()->GetPosition().x, this->gameObject->getBody()->GetPosition().y - 5);
		this->gameObject->getBody()->SetTransform(b2Vec2(this->gameObject->getBody()->GetPosition().x, this->gameObject->getBody()->GetPosition().y - 5), 0);
	}
	if (direction == "move-left")
	{
		direction = "move-right";
		this->gameObject->setPosition(this->gameObject->getBody()->GetPosition().x - 5, this->gameObject->getBody()->GetPosition().y);
		this->gameObject->getBody()->SetTransform(b2Vec2(this->gameObject->getBody()->GetPosition().x - 5, this->gameObject->getBody()->GetPosition().y), 0);
	}
	else if (direction == "move-right")
	{
		direction = "move-left";
		this->gameObject->setPosition(this->gameObject->getBody()->GetPosition().x + 5, this->gameObject->getBody()->GetPosition().y);
		this->gameObject->getBody()->SetTransform(b2Vec2(this->gameObject->getBody()->GetPosition().x + 5, this->gameObject->getBody()->GetPosition().y), 0);
	}
}