#include "stdafx.h"
#include "Bullet.h"

#include "Player.h"

#include "GameObjectContainer.h"
#include "DrawContainer.h"
#include "MoveContainer.h"

#include "NormalDrawBehaviour.h"
#include "ShotMoveBehaviour.h"

Bullet::Bullet(GameObjectContainer * gameObjectContainer, std::map<std::string, std::string>& properties, b2World * world, MoveContainer * moveContainer, DrawContainer * drawContainer, std::string texture) : GameObject{ drawContainer, gameObjectContainer, texture }
{
	this->setProperties(properties);

	this->setMoveContainer(moveContainer);
	ShotMoveBehaviour* moveBehaviour = new ShotMoveBehaviour(this, properties["direction"]);
	this->SetMoveBehaviour(moveBehaviour);
	moveContainer->AddBehaviour(moveBehaviour);

	int x = std::stoi(properties["x"]);
	int y = std::stoi(properties["y"]);
	this->setPosition(x, y);
	this->setSize(8, 8);
	this->createBoxDynamic(*world);
	this->getBody()->SetBullet(true);
}

Bullet::~Bullet()
{
}

void Bullet::startContact(b2Fixture * fixture)
{
	GameObject* pal = static_cast<Player*>(fixture->GetBody()->GetUserData());

	if (dynamic_cast<Unit*> (pal) && !dynamic_cast<Player*> (pal))
	{
		Unit* enemy = dynamic_cast<Unit*> (pal);
		enemy->Damage(this->damage);
	}

	if (!dynamic_cast<Player*> (pal) && !fixture->IsSensor()) {
		Destroy();
	}
}

void Bullet::endContact(b2Fixture * fixture)
{

}