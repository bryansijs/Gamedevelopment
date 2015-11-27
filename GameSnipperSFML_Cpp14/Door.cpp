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
	this->shouldUpdate = true;
}


Door::Door(DrawContainer* container) :GameObject{ container } {
};


Door::Door(DrawContainer* container, std::string img) :GameObject{ container, img } {
};

Door::Door(GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height) :GameObject{ gameObjectContainer } {
	this->useImage = false;
	this->setPosition(position);
	this->setSize(widht, height);
};

Door::Door(DrawContainer* container, std::string img, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height) :GameObject{ container,gameObjectContainer,img } {
	this->useImage = true;
	this->setPosition(position);
	this->setSize(widht, height);
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

void Door::setDoorState()
{
	for (int i = 0; i < DoorList.size(); i++)
		DoorList.at(i)->isVisible = this->isOpen;

	for (int i = 0; i < ofDoorList.size(); i++)
		ofDoorList.at(i)->isVisible = !this->isOpen;
}

