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
#include "Gun.h"
#include "Bullet.h"
#include "GameContext.h"

#include "GameObjectFactory.h"
#include "FilterEnum.h"
ShootAction::ShootAction()
{
}

ShootAction::~ShootAction()
{
}
 
void ShootAction::Shoot(DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world, Player* player, std::string direction, GameContext* gameContext)
{
	if (Time::runningTime > nextShot)
	{
		Gun* gun = (Gun*)player->GetEquipedGun();

		nextShot = (float)Time::runningTime + gun->GetFireRate();

		float x = 0;
		float y = 0;

		if (direction == "move-up")
		{
			x = player->getBody()->GetPosition().x + -2;
			y = player->getBody()->GetPosition().y + -40;
		}
		if (direction == "move-down")
		{
			x = player->getBody()->GetPosition().x + -2;
			y = player->getBody()->GetPosition().y + 40;
		}
		if (direction == "move-left")
		{
			x = player->getBody()->GetPosition().x + -40;
			y = player->getBody()->GetPosition().y + -2;
		}
		if (direction == "move-right")
		{
			x = player->getBody()->GetPosition().x + 40;
			y = player->getBody()->GetPosition().y + -2;
		}

		std::string projectileType = gun->GetProjectileType();

		ProjectileFactory projectileFactory;
		std::map<std::string, std::string> properties = {
			{ "type", "Projectile" },
			{ "pType", projectileType },
			{ "direction", direction },
			{ "texture", gun->GetBulletTexture() },
			{ "damage", std::to_string(gun->GetDamage() * gameContext->damageMultiplier) },
			{ "x", std::to_string(x) },
			{ "y", std::to_string(y) },
			{ "Category", "ENEMY" }
		};

		Bullet* bullet = (Bullet*)projectileFactory.Create(properties, drawContainer, moveContainer, gameObjectContainer, world);
		bullet->SetContext(gameContext);
	}
}