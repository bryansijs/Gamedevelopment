#include "stdafx.h"
#include "ShootAction.h"

#include "Time.h"
#include "GameObject.h"
#include "DrawContainer.h"
#include "MoveContainer.h"
#include "ShotMoveBehaviour.h"
#include "Player.h"

ShootAction::ShootAction()
{
}

ShootAction::~ShootAction()
{
}
 
void ShootAction::Shoot(DrawContainer* drawContainer, MoveContainer* moveContainer, Player* player, std::string direction)
{
	if (Time::runningTime > nextShot)
	{
		nextShot = (float)Time::runningTime + (float)shotRate;

		GameObject* shot = new GameObject(drawContainer, "bullet-red.png");
		ShotMoveBehaviour* shotBehaviour = new ShotMoveBehaviour(shot, direction);

		moveContainer->AddBehaviour(shotBehaviour);
		
		if (direction == "move-up")
		{
		shot->setPosition(sf::Vector2f(player->getPositionX() + 12, player->getPositionY()));
		}
		if (direction == "move-down")
		{
			shot->setPosition(sf::Vector2f(player->getPositionX() + 12, player->getPositionY() + 24));
		}
		if (direction == "move-left")
		{
			shot->setPosition(sf::Vector2f(player->getPositionX(), player->getPositionY() + 12));
		}
		if (direction == "move-right")
		{
			shot->setPosition(sf::Vector2f(player->getPositionX() + 24, player->getPositionY() + 12));
		}
		
		shot->setSize(8, 8);
	}
}