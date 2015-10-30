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
	if(!player->isColliding(*tiles, 5.0f, 5.0f))
	{
		std::cout << "Coliding testing nog impmementeren. " << std::endl;
	}

	if (direction == "move-up")
	{
		player->set_Image_y(3);
		player->position.y += -velocity * Time::deltaTime;
	}
	if (direction == "move-down")
	{
		player->set_Image_y(0);
		player->position.y += velocity * Time::deltaTime;
	}
	if (direction == "move-left")
	{
		player->set_Image_y(1);
		player->position.x += -velocity * Time::deltaTime;
	}
	if (direction == "move-right")
	{
		player->set_Image_y(2);
		player->position.x += velocity * Time::deltaTime;
	}
}