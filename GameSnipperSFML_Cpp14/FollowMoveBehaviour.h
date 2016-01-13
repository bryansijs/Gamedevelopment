#pragma once
#include "MoveBehaviour.h"
#include "MoveAction.h"
#include <vector>
#include <SFML\System\Vector2.hpp>

class BaseEnemy;

class FollowMoveBehaviour : public MoveBehaviour
{
public:
	FollowMoveBehaviour(GameObject* gameObject);
	~FollowMoveBehaviour();

	void Update(sf::Vector2f viewPortPosition);

private:
	MoveAction* moveAction;
	void setDirection();
	std::string mDircection;
	void finalizeDirection();
};

