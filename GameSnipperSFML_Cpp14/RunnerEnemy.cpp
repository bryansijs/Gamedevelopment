#include "stdafx.h"
#include "RunnerEnemy.h"

#include "WanderMoveBehaviour.h"

RunnerEnemy::RunnerEnemy(DrawContainer* container) :Unit{ container } {
};


RunnerEnemy::RunnerEnemy(DrawContainer* container, std::string img) :Unit{ container, img } {
};


RunnerEnemy::RunnerEnemy(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height) :Unit{ container, img } {
	this->setPosition(position);
	this->setSize(widht, height);

	this->SetAnimationStates(4);
};


RunnerEnemy::RunnerEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height) :Unit{ dContainer,img,mContainer,gameObjectContainer } {

	this->SetMoveBehaviour(new WanderMoveBehaviour(this));

	this->setPosition(position);
	this->setSize(widht, height);

	this->SetAnimationStates(4);
};

RunnerEnemy::~RunnerEnemy()
{
}
