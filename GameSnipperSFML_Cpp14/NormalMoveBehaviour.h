#pragma once
#include "MoveBehaviour.h"

#include <SFML\System\Vector2.hpp>

class NormalMoveBehaviour : public MoveBehaviour
{
public:
	NormalMoveBehaviour(GameObject* gameObject);
	~NormalMoveBehaviour();

	void Update(sf::Vector2f viewPortPosition);
	bool checkVisible(int screenX, int screenY);
};

