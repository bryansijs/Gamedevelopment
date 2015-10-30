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
		temp += -0.5;

		if (!player->isColliding(*tiles, player->position.x, temp)) {
			player->position.y += -0.5;
		}
	}
	if (direction == "move-down")
	{
		temp = player->position.y;
		temp += 0.5;
		if (!player->isColliding(*tiles, player->position.x, temp)) {
			player->position.y += 0.5;
		}
	}
	if (direction == "move-left")
	{
		temp = player->position.x;
		temp += -0.5;
		if (!player->isColliding(*tiles, temp, player->position.y)) {
			player->position.x += -0.5;
		}
	}
	if (direction == "move-right")
	{
		temp = player->position.x;
		temp += 0.5;
		if (!player->isColliding(*tiles, temp, player->position.y)) {
			player->position.x += 0.5;
		}
	}
}