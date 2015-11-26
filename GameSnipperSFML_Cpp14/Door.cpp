#include "stdafx.h"
#include "Door.h"


Door::Door()
{
}


Door::~Door()
{
}


void Door::setProperties(std::map<std::string, std::string>& properties) {

	this->keyNeed = (properties.count("keyNeed")) ? std::stoi(properties["xIndex"]) : 0;
	this->setImageX((properties.count("xIndex")) ? std::stoi(properties["xIndex"]) : 0);


}


Door::Door(DrawContainer* container) :GameObject{ container } {
};


Door::Door(DrawContainer* container, std::string img) :GameObject{ container, img } {
};


Door::Door(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height) :GameObject{ container, img } {
	this->setPosition(position);
	this->setSize(widht, height);
};


