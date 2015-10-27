#include "stdafx.h"
#include "MoveAction.h"

#include "Player.h"
#include "Time.h"

#include <iostream>

MoveAction::MoveAction()
{
}

MoveAction::~MoveAction()
{
}

void MoveAction::Move(std::string direction, Player *player)
{
	if (direction == "move-up")
	{
		player->position.y += -velocity * Time::deltaTime;
	}
	if (direction == "move-down")
	{
		player->position.y += velocity * Time::deltaTime;
	}
	if (direction == "move-left")
	{
		player->position.x += -velocity * Time::deltaTime;
	}
	if (direction == "move-right")
	{
		player->position.x += velocity * Time::deltaTime;
	}
}