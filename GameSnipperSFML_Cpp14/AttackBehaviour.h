#pragma once
#include "MoveBehaviour.h"

class MoveAction;

class AttackBehaviour : public MoveBehaviour
{
public:
	AttackBehaviour(GameObject* gameObject);
	~AttackBehaviour();
	void Update(sf::Vector2f viewPortPosition);

private:
	MoveAction* moveAction;

	int agression;
	int aggresionTime;
	float shootDelay = 20;
};

