#include "stdafx.h"
#include "RunnerEnemy.h"


RunnerEnemy::RunnerEnemy(DrawContainer* container) :Unit{ container } {
};


RunnerEnemy::RunnerEnemy(DrawContainer* container, std::string img) :Unit{ container, img } {
};


RunnerEnemy::RunnerEnemy(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height) :Unit{ container, img } {
	this->setPosition(position);
	this->setSize(widht, height);
};


RunnerEnemy::RunnerEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, sf::Vector2f position, int widht, int height) :Unit{ dContainer, img } {
	this->setMoveContainer(mContainer);

	//TODO Iemand:Basic moveBahavoir for this Enemy;
	this->SetMoveBehaviour(nullptr);

	this->setPosition(position);
	this->setSize(widht, height);
};

RunnerEnemy::~RunnerEnemy()
{
}
