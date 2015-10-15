#pragma once
#include "Unit.h"

class MoveBehaviour
{
public:

	virtual void Move(float DOWN, float UP, float RIGHT, float LEFT, float deltaTime); //in pixelsaSecond (DOWN, UP, RIGHT, LEFT)
	virtual bool checkVisible(int screenX, int screenY);

	float getX();
	float getY();
	Unit* getUnit();

protected:
	Unit* unit;
	float xPosition = 0;
	float yPosition = 0;

};

