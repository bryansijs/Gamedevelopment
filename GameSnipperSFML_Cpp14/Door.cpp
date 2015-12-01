#include "stdafx.h"
#include "Door.h"


Door::Door()
{
}


Door::~Door()
{
}

void Door::setProperties(std::map<std::string, std::string>& properties) {
	this->doorId = (properties.count("doorId")) ? std::stoi(properties["doorId"]) : -1;
	this->keyNeed = (properties.count("keyNeed")) ? std::stoi(properties["keyNeed"]) : 0;
	this->switchNeed = (properties.count("switchNeed")) ? std::stoi(properties["switchNeed"]) : 0;
	this->isCollidable = (properties.count("isCollidable")) ? std::stoi(properties["isCollidable"]) : 0;
	this->isOpen = false;
	if (useImage) {
		this->setImageX((properties.count("xIndex")) ? std::stoi(properties["xIndex"]) : 0);
		this->closedState = (properties.count("closedIndex")) ? std::stoi(properties["closedIndex"]) : 0;
		this->openState = (properties.count("openIndex")) ? std::stoi(properties["openIndex"]) : 3;

		if (this->isOpen)
			this->setImageY(openState);
		else
			this->setImageY(closedState);
	}

	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);

	this->setPosition(x, y);
	this->setSize(widht, height);
	this->shouldUpdate = true;
}


Door::Door(DrawContainer* container) :GameObject{ container } {
};


Door::Door(DrawContainer* container, std::string img) :GameObject{ container, img } {
};

Door::Door(GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, std::vector<Tile*>& tiles, b2World* world) :GameObject{ gameObjectContainer } {

	this->setProperties(properties);
	this->setTiles(tiles);
	this->useImage = false;

	//TODO: Set me for body pls!
	this->createBoxStatic(*world);

};


Door::Door(DrawContainer* container, std::string img, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, std::vector<Tile*>& tiles, b2World* world) :GameObject{ container,gameObjectContainer,img } {
	this->useImage = true;

	this->setProperties(properties);
	this->setTiles(tiles);

	//TODO: Set me for body pls!
	//this->createBoxStatic(*world);
};

void Door::doAction()
{
	shouldUpdate = true;
	setOpen();
}

void Door::doAction(Player* player)
{
	if (this->isOpen = true)return;

	if (keyNeed && keyUsed == false)
		if (player->getKey() > 0) {
			player->removeKey();
			this->keyUsed = true;
		}
		else
			return;

	if (switchNeed)
		return;

	shouldUpdate = true;
	setOpen();

}

void Door::setOpen()
{
	isOpen = !isOpen;
	isCollidable = isOpen;
	if (!isOpen) {
		this->setImageY(openState);
		this->getBody()->SetActive(false);
	}
	else if (isOpen) {
		this->setImageY(closedState);
		this->getBody()->SetActive(true);
	}
	this->setDoorState();
}

void Door::setDoorState()
{
	for (int i = 0; i < DoorList.size(); i++)
		DoorList.at(i)->isVisible = this->isOpen;

	for (int i = 0; i < ofDoorList.size(); i++)
		ofDoorList.at(i)->isVisible = !this->isOpen;
}

