#include "stdafx.h"
#include "TankEnemy.h"

#include "WanderMoveBehaviour.h"

TankEnemy::TankEnemy(DrawContainer* container) :Unit{ container } {
};


TankEnemy::TankEnemy(DrawContainer* container, std::string img) :Unit{ container, img } {
};


TankEnemy::TankEnemy(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height) :Unit{ container, img } {
	this->setPosition(position);
	this->setSize(widht, height);

	this->SetAnimationStates(4);
};


TankEnemy::TankEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height) :Unit{ dContainer, img,mContainer,gameObjectContainer } {

	this->SetMoveBehaviour(new WanderMoveBehaviour(this));

	this->setPosition(position);
	this->setSize(widht, height);

	this->SetAnimationStates(4);
};

TankEnemy::~TankEnemy()
{
}
