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


Key::Key(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height) :GameObject{ container, img } {
	this->setPosition(position);
	this->setSize(widht, height);
};

