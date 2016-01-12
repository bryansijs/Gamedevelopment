#include "stdafx.h"
#include "BasicEnemy.h"
#include <cmath>
#include "WanderMoveBehaviour.h"

BasicEnemy::BasicEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, b2World* world) :BaseEnemy{ dContainer, img,mContainer, gameObjectContainer }
{
	

	this->setSpeed(40.f);
	this->setBulletDamageBig(20);
	this->setBulletDamage(10);
	this->setMaxHealth(100);
	this->setHealth(100);

	this->setSeeLengt(200);
	this->setSeeWidth(50);

	this->setMaxWanderDistance(200);
	this->setMinWanderDistance(50);
	this->setDefaultWanderDistance(20);

	this->isCollidable = true;

	this->setProperties(properties);
	this->SetAnimationStates(4);
	this->createBoxDynamic(*world);
	this->CreateLineOfSight();

	this->setPattern();

	this->setAttackType(0);
	this->setPatternAmount(1);
	this->shotRate = 0.15f;
};

BasicEnemy::~BasicEnemy()
{
}

void BasicEnemy::setPattern()
{
	this->PatternSet.insert(std::pair<std::string, float>("0009", 0.50f));
}
