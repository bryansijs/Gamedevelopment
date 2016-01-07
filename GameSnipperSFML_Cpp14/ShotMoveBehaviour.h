#pragma once
#include "MoveBehaviour.h"

#include <iostream>

class ShotMoveBehaviour : public MoveBehaviour
{
public:
	ShotMoveBehaviour(GameObject* gameObject);
	ShotMoveBehaviour(GameObject* gameObject, std::string shotDirection);
	~ShotMoveBehaviour();

	void Update(sf::Vector2f viewPortPosition);
	bool checkVisible(int screenX, int screenY);

	void SetDirection(std::string direction);
private:
	std::string direction;
	int velocity = 500.0f;
};