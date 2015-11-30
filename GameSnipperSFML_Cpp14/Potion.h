#pragma once
#include "BaseItem.h"


class Player;
class DrawContainer;
class GameObjectContainer;

class Potion : public BaseItem
{

private: 
	std::string potionType;
	int potionId;

public:
	Potion();
	~Potion();

	Potion(DrawContainer* container, std::string img,GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties);


	virtual void setProperties(std::map<std::string, std::string>& properties);
	virtual void doAction(Player* player);
};

