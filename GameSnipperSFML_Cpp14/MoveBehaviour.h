#pragma once

#include "GameObject.h"

class MoveBehaviour
{
public:
	virtual void Update();
	virtual bool checkVisible(int screenX, int screenY);

	GameObject* getGameObject() { return gameObject; };
protected:
	GameObject* gameObject;
	float xPosition = 0;
	float yPosition = 0;
};

