#pragma once
#include <map>
#include <string>
#include  <memory>
#include "GameObject.h"


class GameObject;
class Tile;
class InteractiveFactory
{
public:
	InteractiveFactory();
	~InteractiveFactory();
	GameObject* Create(std::map<std::string, std::string> properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, std::vector<Tile*> tileList);


private:
	std::vector<Tile*> tileList;
	GameObject* CreateSwitch(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer);
	GameObject* CreateDoor(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer);
	GameObject* CreateKeyHole(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer);
	std::map<std::string, GameObject*(InteractiveFactory::*)(std::map<std::string, std::string>&, DrawContainer* container, GameObjectContainer* gameObjectContainer)> possibleObjects = {
		{ "Switch", &InteractiveFactory::CreateSwitch },
		{ "Door", &InteractiveFactory::CreateDoor },
		{ "KeyHole", &InteractiveFactory::CreateKeyHole }, };

};

