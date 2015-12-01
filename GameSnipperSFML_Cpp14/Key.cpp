#include "stdafx.h"
#include "Key.h"
#include "DrawContainer.h"
#include "GameObjectContainer.h"


Key::Key()
{
}


Key::~Key()
{
}

void Key::setProperties(std::map<std::string, std::string>& properties) {
	this->setItemType(properties["iType"]);

	this->isCollidable = (properties.count("isCollidable")) ? std::stoi(properties["isCollidable"]) : 0;

	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);

	this->setPosition(x, y);
	this->setSize(widht, height);


}

Key::Key(DrawContainer* container, std::string img, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties,b2World* world) :BaseItem{ container,gameObjectContainer, img  } {
	this->setProperties(properties);
	this->createBoxStatic(*world);
};


void Key::doAction(Player* player)
{
	player->AddItem(this);
	getDrawContainer()->RemoveBehaviour(this->getDrawBehaviour());
	getgameObjectContainer()->RemoveObject(this);
	this->~Key();
}
