#include "stdafx.h"
#include "BasicEnemy.h"

#include "WanderMoveBehaviour.h"

BasicEnemy::BasicEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, b2World* world) :BaseEnemy{ dContainer, img,mContainer, gameObjectContainer }
{
	
	this->isCollidable = true;

	this->setProperties(properties);
	this->SetAnimationStates(4);
	this->createBoxDynamic(*world);
	this->CreateLineOfSight();
	//this->setImageY(2);
};

BasicEnemy::~BasicEnemy()
{
}
