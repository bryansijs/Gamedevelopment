#pragma once
#include "MoveBehaviour.h"

#include <iostream>

class ShotMoveBehaviour : public MoveBehaviour
{
public:
	ShotMoveBehaviour(GameObject* gameObject);
	~ShotMoveBehaviour();

	void Update();
	void SetDirection(std::string shotDirection);
	bool checkVisible(int screenX, int screenY);
private:
	std::string direction;
	int velocity = 6.0f;
};