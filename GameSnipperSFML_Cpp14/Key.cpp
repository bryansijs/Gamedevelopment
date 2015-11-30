#include "stdafx.h"
#include "Key.h"


Key::Key()
{
}


Key::~Key()
{
}

void Key::setProperties(std::map<std::string, std::string>& properties) {

}


Key::Key(DrawContainer* container) :GameObject{ container } {
};


Key::Key(DrawContainer* container, std::string img) :GameObject{ container, img } {
};


Key::Key(DrawContainer* container, std::string img, GameObjectContainer* gameObjectContainer, b2Vec2 position, int widht, int height) :GameObject{ container,gameObjectContainer, img  } {
	this->setPosition(position.x, position.y);
	this->setSize(widht, height);
};

