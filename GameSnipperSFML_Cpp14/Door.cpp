#include "stdafx.h"
#include "Door.h"


Door::Door()
{
}


Door::~Door()
{
}


void Door::setProperties(std::map<std::string, std::string>& properties) {
	this->keyNeed = (properties.count("keyNeed")) ? std::stoi(properties["keyNeed"]) : 0;
	this->switchNeed = (properties.count("switchNeed")) ? std::stoi(properties["switchNeed"]) : 0;
	this->setImageX((properties.count("xIndex")) ? std::stoi(properties["xIndex"]) : 0);
	this->ofState = (properties.count("ofIndex")) ? std::stoi(properties["ofIndex"]) : 0;
	this->onState = (properties.count("onIndex")) ? std::stoi(properties["onIndex"]) : 3;

	if (this->isOpen)
		this->setImageY(onState);
	else
		this->setImageY(ofState);

	this->shouldUpdate = true;

}


Door::Door(DrawContainer* container) :GameObject{ container } {
};


Door::Door(DrawContainer* container, std::string img) :GameObject{ container, img } {
};


Door::Door(DrawContainer* container, std::string img, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height) :GameObject{ container,gameObjectContainer,img  } {
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
	if (isOpen)return;
	if (keyNeed)
		if (player->getKey() > 0)
			player->removeKey();
		else
			return;

	shouldUpdate = true;
	setOpen();
}