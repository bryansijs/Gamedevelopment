#include "stdafx.h"
#include "BasicEnemy.h"

#include "WanderMoveBehaviour.h"

BasicEnemy::BasicEnemy(DrawContainer* container) :Unit{ container }
{
}

BasicEnemy::BasicEnemy(DrawContainer* container, std::string img) :Unit{ container, img }
{
}

BasicEnemy::BasicEnemy(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height) :Unit{ container, img }
{
	this->setPosition(position);
	this->setSize(widht, height);
}

BasicEnemy::BasicEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height) :Unit{ dContainer, img,mContainer, gameObjectContainer }
{
	this->SetMoveBehaviour(new WanderMoveBehaviour(this));
	
	this->setPosition(position);
	this->setSize(widht, height);
}

BasicEnemy::~BasicEnemy()
{
}
