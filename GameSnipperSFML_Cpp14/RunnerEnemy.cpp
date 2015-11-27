#include "stdafx.h"
#include "RunnerEnemy.h"


RunnerEnemy::RunnerEnemy(DrawContainer* container) :Unit{ container } {
};


RunnerEnemy::RunnerEnemy(DrawContainer* container, std::string img) :Unit{ container, img } {
};


RunnerEnemy::RunnerEnemy(DrawContainer* container, std::string img, b2Vec2 position, int widht, int height) :Unit{ container, img } {
	this->setPosition(position);
	this->setSize(widht, height);
};


RunnerEnemy::RunnerEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, b2Vec2 position, int widht, int height) :Unit{ dContainer,img,mContainer,gameObjectContainer } {

	//TODO Iemand:Basic moveBahavoir for this Enemy;
	this->SetMoveBehaviour(nullptr);

	this->setPosition(position);
	this->setSize(widht, height);
};

RunnerEnemy::~RunnerEnemy()
{
}
