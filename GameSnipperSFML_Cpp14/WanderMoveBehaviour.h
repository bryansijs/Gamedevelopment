#pragma once
#include "MoveBehaviour.h"

#include "MoveAction.h"

#include <vector>
#include <SFML\System\Vector2.hpp>

class WanderMoveBehaviour : public MoveBehaviour
{
public:
	WanderMoveBehaviour(GameObject* gameObject);
	~WanderMoveBehaviour();

	void Update(sf::Vector2f viewPortPosition);
	bool checkVisible(int screenX, int screenY);

	

private:
	MoveAction* moveAction;
	void setDirection();
	int defaultMoveDistance = 20;
	int minMoveDistance = 200;
	int maxMoveDistance = 400;

	int moveDistance;
	
	b2Vec2 startPosition;
	b2Vec2 endPosition;

	std::string direction;

	std::vector<std::string> directions = {
		{ "move-up" },
		{ "move-down" },
		{ "move-left" },
		{ "move-right" }
	};
};

