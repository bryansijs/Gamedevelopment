#include "stdafx.h"
#include "MoveAction.h"

#include "Player.h"
#include "Time.h"
#include "Tile.h"

#include <math.h>
#include <iostream>

MoveAction::MoveAction()
{
}

MoveAction::~MoveAction()
{
}

void MoveAction::Move(std::vector<std::string> directions, Player *player, std::vector<Tile>* tiles)
{
	for (std::vector<std::string>::iterator it = directions.begin(); it != directions.end(); ++it)
	{
		if (*it == "move-up")
		{
			player->set_Image_y(3);
			velocity.y -= speed;
		}
		if (*it == "move-down")
		{
			player->set_Image_y(0);
			velocity.y += speed;
		}
		if (*it == "move-left")
		{
			player->set_Image_y(1);
			velocity.x -= speed;
		}
		if (*it == "move-right")
		{
			player->set_Image_y(2);
			velocity.x += speed;
		}
	}

	if (directions.size() == 2)
	{
		velocity.x = velocity.x * cos(45 * 3.14159265359 / 180);
		velocity.y = velocity.y * sin(45 * 3.14159265359 / 180);
	}

	velocity *= Time::deltaTime;

	if (player->isColliding(*tiles, velocity))
	{
		return;
	}

	player->position += velocity;

	/*float temp = 0;
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
	}*/
}