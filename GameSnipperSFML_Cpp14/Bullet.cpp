#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "BaseEnemy.h"
#include "GameObjectContainer.h"
#include "Tile.h"
#include "DrawContainer.h"
#include "MoveContainer.h"
#include "NormalDrawBehaviour.h"
#include "ShotMoveBehaviour.h"
#include "FilterEnum.h"
#include "FollowMoveBehaviour.h"

Bullet::Bullet(GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, b2World* world, MoveContainer* moveContainer, DrawContainer* drawContainer, std::string texture) : GameObject{ drawContainer, gameObjectContainer, texture }
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

void Bullet::SetContext(GameContext* context)
{
	this->context = context;
}

void Bullet::startContact(b2Fixture * fixture)
{
	if (fixture->IsSensor())return;

	GameObject* pal = static_cast<Unit*>(fixture->GetBody()->GetUserData());

	if (dynamic_cast<Unit*> (pal))
	{
		if (dynamic_cast<Player*> (pal))
		{
			if (dynamic_cast<Player*> (pal)->GetGodMode())
			{

				Destroy();
				return;
			}
		
		}

		bool collide =
			(this->getBody()->GetFixtureList()->GetFilterData().maskBits & fixture->GetFilterData().categoryBits) != 0 &&
			(this->getBody()->GetFixtureList()->GetFilterData().categoryBits & fixture->GetFilterData().maskBits) != 0;

		if (collide)
		{     

 			Unit* unit = dynamic_cast<Unit*> (pal);
			
			if (!unit->getVisible())
			{
				Destroy();
				if (dynamic_cast<BaseEnemy*> (unit))
				{
					unit->getBody()->SetLinearVelocity(b2Vec2(0, 0));
				}

				return;
			}
			
   			unit->Damage(this->damage);

			if (dynamic_cast<BaseEnemy*> (pal))
			{
				
				BaseEnemy* enemy = dynamic_cast<BaseEnemy*> (pal);
				enemy->setTarget(this->context->player);
				enemy->setAttacking();
				enemy->addAggressiveTime(20.0f);
			}
			
		}
	}


	Destroy();
}

void Bullet::endContact(b2Fixture * fixture)
{

}