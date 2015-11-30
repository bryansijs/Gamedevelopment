#pragma once
#include "BaseItem.h"
#include "Player.h";

class Player;
class DrawContainer;
class GameObjectContainer;


class Key : public BaseItem
{
public:
	Key();
	~Key();

	Key(DrawContainer* container, std::string img,GameObjectContainer* gameObjectContainer,std::map<std::string, std::string>& properties);


	virtual void setProperties(std::map<std::string, std::string>& properties);
	virtual void doAction(Player* player);
};

