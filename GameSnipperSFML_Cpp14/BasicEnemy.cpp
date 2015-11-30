#include "stdafx.h"
#include "BasicEnemy.h"


BasicEnemy::BasicEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height) :BaseEnemy{ dContainer, img,mContainer, gameObjectContainer } {

	//TODO Iemand:Basic moveBahavoir for this Enemy;
	this->SetMoveBehaviour(nullptr);
	


};


BasicEnemy::BasicEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties
	) :BaseEnemy{ dContainer, img,mContainer, gameObjectContainer } {

	//TODO Iemand:Basic moveBahavoir for this Enemy;
	this->SetMoveBehaviour(nullptr);
	this->isCollidable = true;
	this->setProperties(properties);
};

BasicEnemy::~BasicEnemy()
{
}
