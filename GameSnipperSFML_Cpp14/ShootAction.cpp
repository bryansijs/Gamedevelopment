#include "stdafx.h"
#include "ShootAction.h"

#include <iostream>
#include <map>

#include "Time.h"
#include "GameObject.h"
#include "DrawContainer.h"
#include "MoveContainer.h"
#include "GameObjectContainer.h"
#include "ShotMoveBehaviour.h"
#include "Player.h"

#include "GameObjectFactory.h"

ShootAction::ShootAction()
{
}

ShootAction::~ShootAction()
{
}
 
void ShootAction::Shoot(DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world, Player* player, std::string direction)
{
	if (Time::runningTime > nextShot)
	{
		nextShot = (float)Time::runningTime + (float)shotRate;

		float x = 0;
		float y = 0;

		if (direction == "move-up")
		{
			x = player->getBody()->GetPosition().x + 12;
			y = player->getBody()->GetPosition().y;
		}
		if (direction == "move-down")
		{
			x = player->getBody()->GetPosition().x + 12;
			y = player->getBody()->GetPosition().y + 24;
		}
		if (direction == "move-left")
		{
			x = player->getBody()->GetPosition().x;
			y = player->getBody()->GetPosition().y + 12;
		}
		if (direction == "move-right")
		{
			x = player->getBody()->GetPosition().x + 24;
			y = player->getBody()->GetPosition().y + 12;
		}

		GameObjectFactory gameObjectFactory{ drawContainer, moveContainer, gameObjectContainer, world };
		std::map<std::string, std::string> properties = {
			{ "type", "Projectile" },
			{ "pType", "Bullet" },
			{ "direction", direction },
			{ "texture", "bullet-red.png" },
			{ "x", std::to_string(x) },
			{ "y", std::to_string(y) }
		};
		GameObject* bullet = gameObjectFactory.Create(properties);
	}
}