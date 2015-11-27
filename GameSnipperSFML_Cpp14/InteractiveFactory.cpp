#include "stdafx.h"
#include "InteractiveFactory.h"
#include "Game_Switch.h"
#include "Door.h"

InteractiveFactory::InteractiveFactory()
{
}


InteractiveFactory::~InteractiveFactory()
{
}


GameObject* InteractiveFactory::Create(std::map<std::string, std::string> properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, std::vector<Tile*>& tileList) {
	this->tileList = tileList;
	std::map<std::string, GameObject*(InteractiveFactory::*)(std::map<std::string, std::string>&, DrawContainer*, GameObjectContainer*)>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++) {
		if (it->first == properties["iType"]) {
			auto function = it->second;
			return (this->*function)(properties, container, gameObjectContainer);
		}
	}

	return nullptr;
}


GameObject* InteractiveFactory::CreateSwitch(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer) {

	std::string imgurl = properties["image"];
	if (imgurl != "")
		return new Game_Switch(container, gameObjectContainer, imgurl, properties, tileList);
	else
		return new Game_Switch(gameObjectContainer, properties, tileList);
}
GameObject* InteractiveFactory::CreateDoor(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer) {
	std::string imgurl = properties["image"];

	if (imgurl != "")
		return new Door(container, imgurl, gameObjectContainer, properties, tileList);
	else
		return  new Door(gameObjectContainer, properties, tileList);
}
GameObject* InteractiveFactory::CreateKeyHole(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer) {
	return nullptr;
}