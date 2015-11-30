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


Door::Door(DrawContainer* container, std::string img, b2Vec2 position, int widht, int height) :GameObject{ container, img } {
	this->setPosition(position.x, position.y);
	this->setSize(widht, height);
};


