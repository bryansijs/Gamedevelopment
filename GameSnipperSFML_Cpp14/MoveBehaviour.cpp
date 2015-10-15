#include "stdafx.h"
#include "MoveBehaviour.h"

//Only for baseclass use. 

void MoveBehaviour::Move(float DOWN, float UP, float RIGHT, float LEFT, float deltaTime) {}

bool MoveBehaviour::checkVisible(int screenX, int screenY) { return false; }

float MoveBehaviour::getX()
{
	return this->xPosition;
}

float MoveBehaviour::getY()
{
	return this->yPosition;
}

Unit* MoveBehaviour::getUnit()
{
	return this->unit;
}