#include "stdafx.h"
#include "BasicEnemy.h"

#include "WanderMoveBehaviour.h"

BasicEnemy::BasicEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height) :BaseEnemy{ dContainer, img,mContainer, gameObjectContainer } {

	//TODO Iemand:Basic moveBahavoir for this Enemy;
	this->SetMoveBehaviour(new WanderMoveBehaviour(this));
	this->SetAnimationStates(4);
};


BasicEnemy::BasicEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties
	) :BaseEnemy{ dContainer, img,mContainer, gameObjectContainer } {

	//TODO Iemand:Basic moveBahavoir for this Enemy;
	this->SetMoveBehaviour(new WanderMoveBehaviour(this));
	this->isCollidable = true;
	this->setProperties(properties);
	this->SetAnimationStates(4);
};

BasicEnemy::~BasicEnemy()
{
}