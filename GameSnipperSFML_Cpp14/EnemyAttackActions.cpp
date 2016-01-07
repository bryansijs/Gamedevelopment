#include "stdafx.h"
#include "EnemyAttackActions.h"
#include "Time.h"
#include "BaseEnemy.h"
#include "GameObjectFactory.h"
#include "MoveBehaviour.h"
EnemyAttackActions::EnemyAttackActions(BaseEnemy* obj)
{
	this->obj = obj;
	this->gameObjectFactory = new GameObjectFactory{ obj->getDrawContainer(), obj->getMoveContainer(), obj->getgameObjectContainer(), obj->theWorld() };
}



EnemyAttackActions::~EnemyAttackActions()
{

}

void EnemyAttackActions::Attack()
{
	if (Time::runningTime > obj->nextShot)
	{
		obj->nextShot = (float)Time::runningTime + (float)obj->shotRate;

		if (obj->getMoveBehaviour()->getDirection().at(0) != "move-not");
		{
			this->direction = obj->getMoveBehaviour()->getDirection().at(0);
		}

		switch (this->obj->getAttacktType())
		{
		case 0:
			SingleShot();
			break;
		case 1:
			DualShot();
		}

		obj->setPatternCount(obj->getPatternCount() + 1);
	}
}

void EnemyAttackActions::SingleShot()
{

	float x = 0, x2 = 0, y = 0, y2 = 0;

	if (this->direction == "move-up")
	{

		y = obj->getBody()->GetPosition().y - 10;
		x = obj->getBody()->GetPosition().x + obj->getWidth() / 2;

	}
	if (this->direction == "move-down")
	{

		y = obj->getBody()->GetPosition().y + obj->getHeight() + 10;

		x = obj->getBody()->GetPosition().x + obj->getWidth() / 2;


	}
	if (this->direction == "move-left")
	{
		x = obj->getBody()->GetPosition().x - 10;


		y = obj->getBody()->GetPosition().y + (obj->getHeight() / 2);

	}
	if (this->direction == "move-right")
	{
		x = obj->getBody()->GetPosition().x + obj->getWidth() + 10;
		y = obj->getBody()->GetPosition().y + (obj->getHeight() / 2);

	}



	std::map<std::string, std::string> properties = {
		{ "type", "Projectile" },
		{ "pType", "Bullet" },
		{ "direction", direction },
		{ "texture",  obj->getBulletTextureBig() + ".png" },
		{ "x", std::to_string(x - 8) },
		{ "y", std::to_string(y - 8) },
		{ "size", std::to_string(16) },
		{ "damage" , std::to_string(obj->getBulletDamageBig())},
		{ "Category", "PLAYER" } };
	gameObjectFactory->Create(properties);
}


void EnemyAttackActions::DualShot() {

	float x = 0, x2 = 0, y = 0, y2 = 0;

	if (this->direction == "move-up")
	{

		y = y2 = obj->getBody()->GetPosition().y - 10;
		x = obj->getBody()->GetPosition().x + obj->getWidth() / 8;
		x2 = obj->getBody()->GetPosition().x + obj->getWidth() / 2;

	}
	if (this->direction == "move-down")
	{

		y = y2 = obj->getBody()->GetPosition().y + obj->getHeight() + 10;

		x = obj->getBody()->GetPosition().x + obj->getWidth() / 8;
		x2 = obj->getBody()->GetPosition().x + obj->getWidth() / 2;

	}
	if (this->direction == "move-left")
	{
		x = x2 = obj->getBody()->GetPosition().x - 10;


		y = obj->getBody()->GetPosition().y + (obj->getHeight() / 2);
		y2 = obj->getBody()->GetPosition().y + (obj->getHeight() / 8);
	}
	if (this->direction == "move-right")
	{
		x = x2 = obj->getBody()->GetPosition().x + obj->getWidth() + 10;
		y = obj->getBody()->GetPosition().y + (obj->getHeight() / 2);
		y2 = obj->getBody()->GetPosition().y + (obj->getHeight() / 8);
	}



	std::map<std::string, std::string> properties = {
		{ "type", "Projectile" },
		{ "pType", "Bullet" },
		{ "direction", direction },
		{ "texture", obj->getBulletTexture() + ".png" },
		{ "x", std::to_string(x) },
		{ "y", std::to_string(y) },
		{ "size", std::to_string(8) },
		{ "damage",  std::to_string(obj->getBulletDamage()) },
		{ "Category", "PLAYER" } };
	gameObjectFactory->Create(properties);

	properties = {
	   { "type", "Projectile" },
	   { "pType", "Bullet" },
	   { "direction", direction },
	   { "texture", obj->getBulletTexture() + ".png" },
	   { "x", std::to_string(x2 - 4) },
	   { "y", std::to_string(y2 - 4) },
	   { "size", std::to_string(8) },
	   { "damage",  std::to_string(obj->getBulletDamage()) },
	   { "Category", "PLAYER" } };

	gameObjectFactory->Create(properties);

}
void EnemyAttackActions::SpreadShot()
{

}
