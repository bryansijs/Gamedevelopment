#include "stdafx.h"
#include "ItemFactory.h"
#include "Potion.h"
#include "Key.h"
ItemFactory::ItemFactory()
{
}


ItemFactory::~ItemFactory()
{
}



GameObject* ItemFactory::Create(std::map<std::string, std::string> properties, DrawContainer* container) {
	std::map<std::string, GameObject*(ItemFactory::*)(std::map<std::string, std::string>&, DrawContainer* container)>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++) {
		if (it->first == properties["iType"]) {
			auto function = it->second;
			return (this->*function)(properties, container);
		}
	}

	return nullptr;
}


//TODO: Naar de juiste items;
GameObject* ItemFactory::CreatePotion(std::map<std::string, std::string>& properties, DrawContainer* container) 
{
	std::string imgurl = properties["image"];
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);
	return new Potion(container, imgurl, sf::Vector2f(x, y), widht, height);
}
GameObject* ItemFactory::CreateGun(std::map<std::string, std::string>& properties, DrawContainer* container)
{
	return nullptr;
}
GameObject* ItemFactory::CreateAmmo(std::map<std::string, std::string>& properties, DrawContainer* container)
{
	return nullptr;
}

GameObject* ItemFactory::CreateKey(std::map<std::string, std::string>& properties, DrawContainer* container)
{
	std::string imgurl = properties["image"];
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);
	return new Key(container, imgurl, sf::Vector2f(x, y), widht, height);
}
