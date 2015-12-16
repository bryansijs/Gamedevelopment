#pragma once

#include "GameObject.h"

class MoveBehaviour
{
public:
	virtual void Update(sf::Vector2f viewPortPosition);
	virtual bool checkVisible(int screenX, int screenY);
	


	GameObject* getGameObject() { return gameObject; };
protected:




	GameObject* gameObject;
};

