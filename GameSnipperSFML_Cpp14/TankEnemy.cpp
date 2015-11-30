#include "stdafx.h"
#include "TankEnemy.h"

TankEnemy::TankEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, b2World* world) :BaseEnemy{ dContainer, img,mContainer, gameObjectContainer } {

	//TODO Iemand:Basic moveBahavoir for this Enemy;
	this->SetMoveBehaviour(nullptr);
	this->isCollidable = true;

	this->setProperties(properties);
	this->createBoxStatic(*world);
};

TankEnemy::~TankEnemy()
{
}
