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

void MoveAction::Move(std::vector<std::string> directions, Player *player, std::vector<Tile*>* tiles)
{
	for (std::vector<std::string>::iterator it = directions.begin(); it != directions.end(); ++it)
	{
		if (*it == "move-up")
		{
			player->setImageY(3);
			velocity.y -= speed;
		}
		if (*it == "move-down")
		{
			player->setImageY(0);
			velocity.y += speed;
		}
		if (*it == "move-left")
		{
			player->setImageY(1);
			velocity.x -= speed;
		}
		if (*it == "move-right")
		{
			player->setImageY(2);
			velocity.x += speed;
		}
	}

	velocity *= Time::deltaTime;

	if (directions.size() == 2)
	{
		velocity.x *= cos(45 * 3.14159265359 / 180);
		velocity.y *= sin(45 * 3.14159265359 / 180);
	}

	if (player->isColliding(*tiles, velocity))
	{
		return;
	}

	velocity.x = roundf(velocity.x * 100) / 100;
	velocity.y = roundf(velocity.y * 100) / 100;

	if(velocity.x != 0 || velocity.y != 0)
		AnimateMovement(player);

	player->setPosition(player->getPosition() + velocity);

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

	player->setImageX(animateState);
	animateState++;
	animationDelay = 0.05;
}

void MoveAction::AnimateMovement(Player* player, int state)
{
	animateState = state;
	AnimateMovement(player);
}