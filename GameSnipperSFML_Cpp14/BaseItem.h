#pragma once
#include "GameObject.h"


class Player;
class DrawContainer;
class GameObjectContainer;


class BaseItem : public GameObject
{

private:
	std::string itemType;
	int itemId;
public:
	BaseItem();
	~BaseItem();

	BaseItem(DrawContainer* container);
	BaseItem(DrawContainer* container, std::string img);
	BaseItem(DrawContainer* container, std::string img, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height);
	BaseItem(DrawContainer* container, GameObjectContainer* gameObjectContainer, std::string img);


		
	virtual void setProperties(std::map<std::string, std::string>& properties);
	virtual void doAction(Player* player);

	std::string getItemType() { return itemType; };
	void setItemType(std::string itemType) { this->itemType = itemType; };

	int getItemId() { return this->itemId; };
	void setItemId(int itemId) { this->itemId = itemId; };
};

