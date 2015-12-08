#include "stdafx.h"
#include "RunnerEnemy.h"

#include "WanderMoveBehaviour.h"

RunnerEnemy::RunnerEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, b2World* world) :BaseEnemy{ dContainer, img,mContainer, gameObjectContainer }
{
	this->SetMoveBehaviour(new WanderMoveBehaviour(this));
	this->SetAnimationStates(4);

	this->isCollidable = true;

	this->setProperties(properties);
	this->createBoxDynamic(*world);
};

RunnerEnemy::~RunnerEnemy()
{
}
