#include "stdafx.h"
#include "WanderMoveBehaviour.h"

#include "Random.h"

#include <cstdlib>

WanderMoveBehaviour::WanderMoveBehaviour(GameObject* gameObject)
{
	this->gameObject = gameObject;
	startPosition = gameObject->getPosition();
	endPosition = gameObject->getPosition();

	moveAction.SetAnimationStates(4);
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
			direction = directions[Random::Number(0, directions.size() - 1)];
		}

		moveAction.Move({ direction }, gameObject);
	}
}

bool WanderMoveBehaviour::checkVisible(int screenX, int screenY)
{
	return (gameObject->getPosition().x > screenX && gameObject->getPosition().x < screenX + 960 && gameObject->getPosition().y > screenY && gameObject->getPosition().y < screenY + 640);
}
