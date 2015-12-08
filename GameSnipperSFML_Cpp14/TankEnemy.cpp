#include "stdafx.h"
#include "TankEnemy.h"

#include "WanderMoveBehaviour.h"

TankEnemy::TankEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, b2World* world) :BaseEnemy{ dContainer, img,mContainer, gameObjectContainer }
{
	this->SetMoveBehaviour(new WanderMoveBehaviour(this));
	this->isCollidable = true;

	this->setProperties(properties);
	this->createBoxDynamic(*world);
};

TankEnemy::~TankEnemy()
{
}
