#include "stdafx.h"
#include "InteractiveFactory.h"
#include "Game_Switch.h"
#include "Door.h"
#include "Discovery.h"

InteractiveFactory::InteractiveFactory()
{
}


InteractiveFactory::~InteractiveFactory()
{
}


GameObject* InteractiveFactory::Create(std::map<std::string, std::string> properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world, std::vector<Tile*>& tileList) {
	this->tileList = tileList;
	std::map<std::string, GameObject*(InteractiveFactory::*)(std::map<std::string, std::string>&, DrawContainer*, GameObjectContainer*, b2World* )>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++) {
		if (it->first == properties["iType"]) {
			auto function = it->second;
			return (this->*function)(properties, container, gameObjectContainer,world);
		}
	}

	return nullptr;
}


GameObject* InteractiveFactory::CreateSwitch(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer ,b2World* world) {

	std::string imgurl = properties["image"];
	if (imgurl != "")
		return new Game_Switch(container, gameObjectContainer, imgurl, properties, tileList, world);
	else
		return new Game_Switch(gameObjectContainer, properties, tileList, world);
}

GameObject* InteractiveFactory::CreateDoor(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world) {
	std::string imgurl = properties["image"];

	if (imgurl != "")
		return new Door(container, imgurl, gameObjectContainer, properties, tileList, world);
	else
		return new Door(gameObjectContainer, properties, tileList, world);
}
GameObject* InteractiveFactory::CreateKeyHole(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world) {
	return nullptr;
}

GameObject * InteractiveFactory::CreateDiscoverObject(std::map<std::string, std::string>& properties, DrawContainer * container, GameObjectContainer * gameObjectContainer, b2World * world)
{
	return new Discovery(container, gameObjectContainer, properties, tileList, world);
}
