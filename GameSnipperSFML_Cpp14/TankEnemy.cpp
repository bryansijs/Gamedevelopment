#include "stdafx.h"
#include "TankEnemy.h"

#include "WanderMoveBehaviour.h"

TankEnemy::TankEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height) :BaseEnemy{ dContainer, img,mContainer,gameObjectContainer } {
	//TODO Iemand:Basic moveBahavoir for this Enemy;
	this->SetMoveBehaviour(nullptr);

	this->setPosition(position);
	this->setSize(widht, height);

	this->SetAnimationStates(4);
	this->isCollidable = true;
};


TankEnemy::TankEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties
	) :BaseEnemy{ dContainer, img,mContainer, gameObjectContainer } {
	this->SetAnimationStates(4);
	//TODO Iemand:Basic moveBahavoir for this Enemy;
	this->SetMoveBehaviour(nullptr);
	this->isCollidable = true;
	this->setProperties(properties);
};

TankEnemy::~TankEnemy()
{
}
