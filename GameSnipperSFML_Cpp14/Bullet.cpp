#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "GameObjectContainer.h"
#include "Tile.h"
#include "DrawContainer.h"
#include "MoveContainer.h"
#include "NormalDrawBehaviour.h"
#include "ShotMoveBehaviour.h"
#include "FilterEnum.h"
Bullet::Bullet(GameObjectContainer * gameObjectContainer, std::map<std::string, std::string>& properties, b2World * world, MoveContainer * moveContainer, DrawContainer * drawContainer, std::string texture) : GameObject{ drawContainer, gameObjectContainer, texture }
{
	this->setProperties(properties);

	this->setMoveContainer(moveContainer);
	ShotMoveBehaviour* moveBehaviour = new ShotMoveBehaviour(this, properties["direction"]);
	this->SetMoveBehaviour(moveBehaviour);
	moveContainer->AddBehaviour(moveBehaviour);

	int x = std::stoi(properties["x"]);
	int y = std::stoi(properties["y"]);
	int size = properties.count("size") ? std::stoi(properties["size"]) : 8;
	this->damage = properties.count("damage") ? std::stoi(properties["damage"]) : 20;
	this->setPosition(x, y);
	this->setSize(size, size);
	this->createBoxDynamic(*world);
	b2Filter fil = this->getBody()->GetFixtureList()->GetFilterData();

	fil.maskBits = FilterEnum::getValue(properties["Category"]) | _entityCategory::TILE | _entityCategory::OBJECT;


	this->getBody()->GetFixtureList()->SetFilterData(fil);
	this->getBody()->SetBullet(true);
}

Bullet::~Bullet()
{
}



void Bullet::startContact(b2Fixture * fixture)
{
	if (fixture->IsSensor())return;
	GameObject* pal = static_cast<Player*>(fixture->GetBody()->GetUserData());

	if (dynamic_cast<Unit*> (pal))
	{
		if (dynamic_cast<Player*> (pal))
		{
			if (dynamic_cast<Player*> (pal)->GetGodMode())
			{
				return;
			}
		
		}

		bool collide =
			(this->getBody()->GetFixtureList()->GetFilterData().maskBits & fixture->GetFilterData().categoryBits) != 0 &&
			(this->getBody()->GetFixtureList()->GetFilterData().categoryBits & fixture->GetFilterData().maskBits) != 0;

		if (collide)
		{
			Unit* enemy = dynamic_cast<Unit*> (pal);
			enemy->Damage(this->damage);
		}
	}

	Destroy();
}

void Bullet::endContact(b2Fixture * fixture)
{

}