#include "stdafx.h"
#include "BasicEnemy.h"
#include <cmath>
#include "WanderMoveBehaviour.h"

BasicEnemy::BasicEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, b2World* world) :BaseEnemy{ dContainer, img,mContainer, gameObjectContainer }
{
	
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
	//this->PatternSet.insert(std::pair<std::string, float>("0009", 0.15f));
	//this->PatternSet.insert(std::pair<std::string, float>("9901", 5.0f));
}
