#include "stdafx.h"
#include "Potion.h"
#include "DrawContainer.h"
#include "GameObjectContainer.h"
#include "Player.h"


Potion::Potion()
{
}


Potion::~Potion()
{
}



void Potion::setProperties(std::map<std::string, std::string>& properties) {
	this->setItemType(properties["iType"]);
	this->setItemId((properties.count("itemId")) ? std::stoi(properties["itemId"]) : 0);
	this->isCollidable = (properties.count("isCollidable")) ? std::stoi(properties["isCollidable"]) : 0;

	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);

	this->setPosition(x, y);
	this->setSize(widht, height);
}



Potion::Potion(DrawContainer* container, std::string img, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, b2World* world) :BaseItem{ container,gameObjectContainer, img } {
	this->setProperties(properties);
	this->createBoxSenor(*world);
};


void Potion::doAction(Player* player)
{
	player->AddItem(this);
	getDrawContainer()->RemoveBehaviour(this->getDrawBehaviour());
	getgameObjectContainer()->RemoveObject(this);
	this->~Potion();
}
