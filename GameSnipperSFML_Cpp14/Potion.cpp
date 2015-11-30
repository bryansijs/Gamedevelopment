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


Potion::Potion(DrawContainer* container, std::string img, GameObjectContainer* gameObjectContainer, b2Vec2 position, int widht, int height) :GameObject{ container,gameObjectContainer, img } {
	this->setPosition(position.x, position.y);
	this->setSize(widht, height);
};


