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
	GameObject* Create(std::map<std::string, std::string> properties, DrawContainer* , GameObjectContainer*, b2World* world, std::vector<Tile*>& );


private:
	std::vector<Tile*> tileList;
	GameObject* CreateSwitch(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world);
	GameObject* CreateDoor(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world);
	GameObject* CreateKeyHole(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world);
	std::map<std::string, GameObject*(InteractiveFactory::*)(std::map<std::string, std::string>&, DrawContainer* , GameObjectContainer* , b2World* )> possibleObjects = {
		{ "Switch", &InteractiveFactory::CreateSwitch },
		{ "Door", &InteractiveFactory::CreateDoor },
		{ "KeyHole", &InteractiveFactory::CreateKeyHole }, };

};

