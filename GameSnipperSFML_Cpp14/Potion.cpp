#include "stdafx.h"
#include "Potion.h"


Potion::Potion()
{
}


Potion::~Potion()
{
}



void Potion::setProperties(std::map<std::string, std::string>& properties) {

}


Potion::Potion(DrawContainer* container) :GameObject{ container } {
};


Potion::Potion(DrawContainer* container, std::string img) :GameObject{ container, img } {
};


Potion::Potion(DrawContainer* container, std::string img, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height) :GameObject{ container,gameObjectContainer, img } {
	this->setPosition(position);
	this->setSize(widht, height);
};


