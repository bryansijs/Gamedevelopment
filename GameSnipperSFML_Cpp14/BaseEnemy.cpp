#include "stdafx.h"
#include "BaseEnemy.h"


BaseEnemy::BaseEnemy()
{
}


BaseEnemy::~BaseEnemy()
{
}


BaseEnemy::BaseEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer) :Unit{ dContainer, img,mContainer, gameObjectContainer } {

}

void BaseEnemy::setProperties(std::map<std::string, std::string>& properties)
{
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);

	this->setPosition(x,y);
	this->setSize(widht, height);
}