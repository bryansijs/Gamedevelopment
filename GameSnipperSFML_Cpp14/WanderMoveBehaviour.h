#pragma once
#include "MoveBehaviour.h"

#include "MoveAction.h"

#include <vector>
#include <SFML\System\Vector2.hpp>

class BaseEnemy;

class WanderMoveBehaviour : public MoveBehaviour
{
public:
	WanderMoveBehaviour(GameObject* gameObject);
	~WanderMoveBehaviour();

	void Update(sf::Vector2f viewPortPosition);
	bool checkVisible(int screenX, int screenY);

private:
	void MoveAway(BaseEnemy* obj);
	MoveAction* moveAction;
	void setDirection();
	int defaultMoveDistance = 20;
	int reverseTime = 20;
	int reversecoolDown = 10;
	int minMoveDistance = 10;
	int maxMoveDistance = 100;

	int moveDistance;
	int currentMoveDistance = 0;
	std::string mDircection;

	void reverseDirection();
	void finalizeDirection();
};

