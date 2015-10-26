#pragma once
#include "MoveBehaviour.h"
class NormalMoveBehaviour : public MoveBehaviour
{
public:
	NormalMoveBehaviour(Unit* unit);
	~NormalMoveBehaviour();

	void Move(float DOWN, float UP, float RIGHT, float LEFT, float deltaTime);
	bool checkVisible(int screenX, int screenY);
};

