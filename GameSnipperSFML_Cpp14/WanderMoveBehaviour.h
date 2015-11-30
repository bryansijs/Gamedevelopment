#pragma once
#include "MoveBehaviour.h"

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
	int defaultMoveDistance = 20;
	int minMoveDistance = 200;
	int maxMoveDistance = 400;

	int moveDistance;
	std::string direction;

	sf::Vector2f startPosition;
	sf::Vector2f endPosition;

	std::vector<std::string> directions = {
		{ "move-up" },
		{ "move-down" },
		{ "move-left" },
		{ "move-right" }
	};
};

