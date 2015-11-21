#include "stdafx.h"
#include "Door.h"


Door::Door()
{
}


Door::~Door()
{
}


void Door::setProperties(std::map<std::string, std::string>& properties) {

}


Door::Door(DrawContainer* container) :GameObject{ container } {
};


Door::Door(DrawContainer* container, std::string img) :GameObject{ container, img } {
};


Door::Door(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height) :GameObject{ container, img } {
	this->setPosition(position);
	this->setSize(widht, height);
};


