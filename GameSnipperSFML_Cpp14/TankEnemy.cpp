#include "stdafx.h"
#include "TankEnemy.h"



TankEnemy::TankEnemy(DrawContainer* container) :Unit{ container } {
};


TankEnemy::TankEnemy(DrawContainer* container, std::string img) :Unit{ container, img } {
};


TankEnemy::TankEnemy(DrawContainer* container, std::string img, b2Vec2 position, int widht, int height) :Unit{ container, img } {
	this->setPosition(position);
	this->setSize(widht, height);
};


TankEnemy::TankEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, b2Vec2 position, int widht, int height) :Unit{ dContainer, img,mContainer,gameObjectContainer } {

	//TODO Iemand:Basic moveBahavoir for this Enemy;
	this->SetMoveBehaviour(nullptr);

	this->setPosition(position);
	this->setSize(widht, height);
};

TankEnemy::~TankEnemy()
{
}
