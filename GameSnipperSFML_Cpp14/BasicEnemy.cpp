#include "stdafx.h"
#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(DrawContainer* container) :Unit{ container } {
};


BasicEnemy::BasicEnemy(DrawContainer* container, std::string img) :Unit{ container, img } {
};


BasicEnemy::BasicEnemy(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height) :Unit{ container, img } {
	this->setPosition(position);
	this->setSize(widht, height);
};


BasicEnemy::BasicEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height) :Unit{ dContainer, img,mContainer, gameObjectContainer } {

	//TODO Iemand:Basic moveBahavoir for this Enemy;
	this->SetMoveBehaviour(nullptr);
	
	this->setPosition(position);
	this->setSize(widht, height);
};

BasicEnemy::~BasicEnemy()
{
}
