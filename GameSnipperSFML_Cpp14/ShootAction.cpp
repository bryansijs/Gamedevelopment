#include "stdafx.h"
#include "ShootAction.h"

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

		GameObjectFactory gameObjectFactory{ drawContainer, moveContainer, gameObjectContainer, world };
		std::map<std::string, std::string> properties = { { "type", "Projectile" },{ "pType", "Bullet" },{ "direction", direction },{ "texture", "bullet-red.png" } };
		GameObject* bullet = gameObjectFactory.Create(properties);
		
		if (direction == "move-up")
		{
			bullet->setPosition(player->getBody()->GetPosition().x + 12, player->getBody()->GetPosition().y);
		}
		if (direction == "move-down")
		{
			bullet->setPosition(player->getBody()->GetPosition().x + 12, player->getBody()->GetPosition().y + 24);
		}
		if (direction == "move-left")
		{
			bullet->setPosition(player->getBody()->GetPosition().x, player->getBody()->GetPosition().y + 12);
		}
		if (direction == "move-right")
		{
			bullet->setPosition(player->getBody()->GetPosition().x + 24, player->getBody()->GetPosition().y + 12);
		}
		
		bullet->setSize(8, 8);
	}
}