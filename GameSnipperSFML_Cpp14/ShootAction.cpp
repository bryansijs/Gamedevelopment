#include "stdafx.h"
#include "ShootAction.h"

#include <map>

#include "Time.h"
#include "GameObject.h"
#include "DrawContainer.h"
#include "MoveContainer.h"
#include "ShotMoveBehaviour.h"
#include "Player.h"

#include "GameObjectFactory.h"

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
		shot->setPosition(player->getBody()->GetPosition().x + 12, player->getBody()->GetPosition().y);
		}
		if (direction == "move-down")
		{
			shot->setPosition(player->getBody()->GetPosition().x + 12, player->getBody()->GetPosition().y + 24);
		}
		if (direction == "move-left")
		{
			shot->setPosition(player->getBody()->GetPosition().x, player->getBody()->GetPosition().y + 12);
		}
		if (direction == "move-right")
		{
			shot->setPosition(player->getBody()->GetPosition().x + 24, player->getBody()->GetPosition().y + 12);
		}
		
		shot->setSize(8, 8);
	}
}