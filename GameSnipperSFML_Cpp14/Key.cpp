#include "stdafx.h"
#include "Key.h"
#include "DrawContainer.h"
#include "GameObjectContainer.h"
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


Key::Key(DrawContainer* container, std::string img, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height) :GameObject{ container,gameObjectContainer, img  } {
	this->setPosition(position);
	this->setSize(widht, height);
};


void Key::doAction(Player* player)
{
	player->AddKey();
	getDrawContainer()->RemoveBehaviour(this->getDrawBehaviour());
	getgameObjectContainer()->RemoveObject(this);
	this->~Key();
}