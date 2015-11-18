#include "stdafx.h"
#include "MoveAction.h"
#include "Player.h"
#include "Time.h"
#include "Tile.h"
#include <iostream>

MoveAction::~MoveAction()
{
}

void MoveAction::Move(std::string direction, Unit *unit, std::vector<Tile>* tiles)
{
	float temp;
	if (direction == "move-up")
	{
		unit->set_Image_y(3);
		temp = unit->position.y;
		temp += -velocity * Time::deltaTime;

		if (!unit->isColliding(*tiles, unit->position.x, temp)) {
			unit->position.y += -velocity * Time::deltaTime;
		}
	}
	if (direction == "move-down")
	{
		unit->set_Image_y(0);
		temp = unit->position.y;
		temp += velocity * Time::deltaTime;
		if (!unit->isColliding(*tiles, unit->position.x, temp)) {
			unit->position.y += velocity * Time::deltaTime;
		}
	}
	if (direction == "move-left")
	{
		unit->set_Image_y(1);
		temp = unit->position.x;
		temp += -velocity * Time::deltaTime;
		if (!unit->isColliding(*tiles, temp, unit->position.y)) {
			unit->position.x += -velocity * Time::deltaTime;
		}
	}
	if (direction == "move-right")
	{
		unit->set_Image_y(2);
		temp = unit->position.x;
		temp += velocity * Time::deltaTime;
		if (!unit->isColliding(*tiles, temp, unit->position.y)) {
			unit->position.x += velocity * Time::deltaTime;
		}
	}
	AnimateMovement(unit);
}

void MoveAction::AnimateMovement(Unit *unit)
{
	if (animationDelay > 0)
	{
		animationDelay = animationDelay - Time::deltaTime;
		return;
	}

	if (animateState == 3)
		animateState = 0;

	unit->set_Image_x(animateState);
	animateState++;
	animationDelay = 9;
}

void MoveAction::AnimateMovement(Unit* unit, int state)
{
	animateState = state;
	AnimateMovement(unit);
}