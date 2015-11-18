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


GameObject* InteractiveFactory::Create(std::map<std::string, std::string> properties, DrawContainer* container) {
	std::map<std::string, GameObject*(InteractiveFactory::*)(std::map<std::string, std::string>&, DrawContainer* container)>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++) {
		if (it->first == properties["iType"]) {
			auto function = it->second;
			return (this->*function)(properties, container);
		}
	}

	return nullptr;
}


GameObject* InteractiveFactory::CreateSwitch(std::map<std::string, std::string>& properties, DrawContainer* container) {
	std::string imgurl = properties["image"];
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);
	if(imgurl != "")
		return  new Game_Switch(container, imgurl, sf::Vector2f(x, y), widht, height);
	else
		return  new Game_Switch(sf::Vector2f(x, y), widht, height);
}
GameObject* InteractiveFactory::CreateDoor(std::map<std::string, std::string>& properties, DrawContainer* container) {
	std::string imgurl = properties["image"];
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);
	return  new Door(container, imgurl, sf::Vector2f(x, y), widht, height);

}
GameObject* InteractiveFactory::CreateKeyHole(std::map<std::string, std::string>& properties, DrawContainer* container) {
	return nullptr;
}