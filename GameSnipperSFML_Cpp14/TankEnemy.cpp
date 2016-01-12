#include "stdafx.h"
#include "TankEnemy.h"

#include "WanderMoveBehaviour.h"

TankEnemy::TankEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, b2World* world) :BaseEnemy{ dContainer, img,mContainer, gameObjectContainer }
{
	this->setSize(38, 54);
	this->isCollidable = true;


	this->setSpeed(20.f);
	this->setBulletDamageBig(40);
	this->setBulletDamage(10);
	this->setMaxHealth(200);
	this->setHealth(200);


	this->setSeeLength(400);
	this->setSeeWidth(100);

	this->setMaxWanderDistance(200);
	this->setMinWanderDistance(50);
	this->setDefaultWanderDistance(20);

	this->setProperties(properties);
	this->SetAnimationStates(4);
	this->createBoxDynamic(*world);
	this->CreateLineOfSight();

	this->setPattern();

	this->setAttackType(2);
	this->setPatternAmount(1);
	this->shotRate = 3.0f;
}

TankEnemy::~TankEnemy()
{
}

void TankEnemy::setPattern()
{
	this->PatternSet.insert(std::pair<std::string, float>("0200", 3.0f));
}