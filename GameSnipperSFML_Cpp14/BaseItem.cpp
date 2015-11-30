#include "stdafx.h"
#include "BaseItem.h"
#include "DrawContainer.h"
#include "GameObjectContainer.h"
#include "Player.h"

BaseItem::BaseItem()
{
}


BaseItem::~BaseItem()
{
}


BaseItem::BaseItem(DrawContainer* container) :GameObject{ container } {
};


BaseItem::BaseItem(DrawContainer* container, std::string img) :GameObject{ container, img } {
};

BaseItem::BaseItem(DrawContainer* container,GameObjectContainer* gameObjectContainer, std::string img) :GameObject{ container,gameObjectContainer, img } {
};




BaseItem::BaseItem(DrawContainer* container, std::string img, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height) :GameObject{ container,gameObjectContainer, img } {
};

void BaseItem::setProperties(std::map<std::string, std::string>& properties) {}
 void BaseItem::doAction(Player* player) {}