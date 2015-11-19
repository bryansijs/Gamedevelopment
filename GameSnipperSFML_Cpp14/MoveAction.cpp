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

	velocity *= Time::deltaTime;

	if (directions.size() == 2)
	{
		velocity.x *= cos(45 * 3.14159265359 / 180);
		velocity.y *= sin(45 * 3.14159265359 / 180);
	}

	std::cout << "X: " << velocity.x << "\n";
	std::cout << "Y: " << velocity.y << "\n";

	if (player->isColliding(*tiles, velocity))
	{
		return;
	}

	velocity.x = roundf(velocity.x * 100) / 100;
	velocity.y = roundf(velocity.y * 100) / 100;

	AnimateMovement(player);

	player->position += velocity;
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
	animationDelay = 0.05;
}

void MoveAction::AnimateMovement(Player* player, int state)
{
	animateState = state;
	AnimateMovement(player);
}