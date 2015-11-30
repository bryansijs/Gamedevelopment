#include "stdafx.h"
#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(DrawContainer* container) :Unit{ container } {
};


BasicEnemy::BasicEnemy(DrawContainer* container, std::string img) :Unit{ container, img } {
};


BasicEnemy::BasicEnemy(DrawContainer* container, std::string img, b2Vec2 position, int widht, int height) :Unit{ container, img } {
	this->setPosition(position.x, position.y);
	this->setSize(widht, height);
};


BasicEnemy::BasicEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, b2Vec2 position, int widht, int height) :Unit{ dContainer, img,mContainer, gameObjectContainer } {

	//TODO Iemand:Basic moveBahavoir for this Enemy;
	this->SetMoveBehaviour(nullptr);
	
	this->setPosition(position.x, position.y);
	this->setSize(widht, height);
};

BasicEnemy::~BasicEnemy()
{
}
