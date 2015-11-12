#include "stdafx.h"
#include "MoveAction.h"
#include "Player.h"
#include "Time.h"
#include "Tile.h"
#include <iostream>

MoveAction::~MoveAction()
{
}

void MoveAction::Move(std::string direction, Player *player, std::vector<Tile>* tiles)
{
	float temp;
	if (direction == "move-up")
	{
		player->set_Image_y(3);
		temp = player->position.y;
		temp += -velocity * Time::deltaTime;

		if (!player->isColliding(*tiles, player->position.x, temp)) {
			player->position.y += -velocity * Time::deltaTime;
		}
	}
	if (direction == "move-down")
	{
		player->set_Image_y(0);
		temp = player->position.y;
		temp += velocity * Time::deltaTime;
		if (!player->isColliding(*tiles, player->position.x, temp)) {
			player->position.y += velocity * Time::deltaTime;
		}
	}
	if (direction == "move-left")
	{
		player->set_Image_y(1);
		temp = player->position.x;
		temp += -velocity * Time::deltaTime;
		if (!player->isColliding(*tiles, temp, player->position.y)) {
			player->position.x += -velocity * Time::deltaTime;
		}
	}
	if (direction == "move-right")
	{
		player->set_Image_y(2);
		temp = player->position.x;
		temp += velocity * Time::deltaTime;
		if (!player->isColliding(*tiles, temp, player->position.y)) {
			player->position.x += velocity * Time::deltaTime;
		}
	}
	AnimateMovement(player);
}

void MoveAction::AnimateMovement(Player *player)
{
	if (animationDelay > 0)
	{
		animationDelay = animationDelay - Time::deltaTime;
		return;
	}

	if (animateState == 3)
		animateState = 0;

	player->set_Image_x(animateState);
	animateState++;
	animationDelay = 5;
}

void MoveAction::AnimateMovement(Player* player, int state)
{
	animateState = state;
	AnimateMovement(player);
}