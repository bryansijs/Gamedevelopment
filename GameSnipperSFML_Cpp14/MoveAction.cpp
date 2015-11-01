#include "stdafx.h"
#include "MoveAction.h"

#include "Player.h"
#include "Time.h"
#include "Tile.h"

#include <iostream>

MoveAction::MoveAction()
{
}

MoveAction::~MoveAction()
{
}

void MoveAction::Move(std::string direction, Player *player, std::vector<Tile>* tiles)
{
	float temp = 0;
	if (direction == "move-up")
	{
		temp = player->position.y;
		temp += -velocity * Time::deltaTime;

		if (!player->isColliding(*tiles, player->position.x, temp)) {
			player->position.y += -velocity * Time::deltaTime;
		}
	}
	if (direction == "move-down")
	{
		temp = player->position.y;
		temp += velocity * Time::deltaTime;
		if (!player->isColliding(*tiles, player->position.x, temp)) {
			player->position.y += velocity * Time::deltaTime;
		}
	}
	if (direction == "move-left")
	{
		temp = player->position.x;
		temp += -velocity * Time::deltaTime;
		if (!player->isColliding(*tiles, temp, player->position.y)) {
			player->position.x += -velocity * Time::deltaTime;
		}
	}
	if (direction == "move-right")
	{
		temp = player->position.x;
		temp += velocity * Time::deltaTime;
		if (!player->isColliding(*tiles, temp, player->position.y)) {
			player->position.x += velocity * Time::deltaTime;
		}
	}
}