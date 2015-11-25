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
	std::map<std::string, GameObject*(InteractiveFactory::*)(std::map<std::string, std::string>&, DrawContainer* , GameObjectContainer* )>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++) {
		if (it->first == properties["iType"]) {
			auto function = it->second;
			return (this->*function)(properties, container, gameObjectContainer);
		}
	}

	return nullptr;
}


GameObject* InteractiveFactory::CreateSwitch(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer) {
	Game_Switch *obj = nullptr;
	std::string imgurl =properties["image"];
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);
	if(imgurl != "")
		obj = new Game_Switch(container, gameObjectContainer, imgurl, sf::Vector2f(x, y), widht, height);
	else
		obj=  new Game_Switch(gameObjectContainer,sf::Vector2f(x, y), widht, height);

	obj->setProperties(properties);
	obj->setTiles(tileList);
	return obj;
}
GameObject* InteractiveFactory::CreateDoor(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer) {
	std::string imgurl = properties["image"];
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);
	return  new Door(container, imgurl, sf::Vector2f(x, y), widht, height);

}
GameObject* InteractiveFactory::CreateKeyHole(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer) {
	return nullptr;
}