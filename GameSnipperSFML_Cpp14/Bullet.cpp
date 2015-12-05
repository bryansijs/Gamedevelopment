#include "stdafx.h"
#include "Bullet.h"

#include "GameObjectContainer.h"
#include "DrawContainer.h"
#include "MoveContainer.h"

#include "NormalDrawBehaviour.h"
#include "ShotMoveBehaviour.h"

Bullet::Bullet(GameObjectContainer * gameObjectContainer, std::map<std::string, std::string>& properties, b2World * world, MoveContainer * moveContainer, DrawContainer * drawContainer, std::string texture) : GameObject{ drawContainer, gameObjectContainer, texture }
{
	this->setProperties(properties);

	ShotMoveBehaviour* moveBehaviour = new ShotMoveBehaviour(this, properties["direction"]);
	this->SetMoveBehaviour(moveBehaviour);
	moveContainer->AddBehaviour(moveBehaviour);

	this->createBoxDynamic(*world);
}

Bullet::~Bullet()
{
}
