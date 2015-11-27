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



GameObject* ItemFactory::Create(std::map<std::string, std::string> properties, DrawContainer* container, GameObjectContainer* gameObjectContainer) {
	std::map<std::string, GameObject*(ItemFactory::*)(std::map<std::string, std::string>&, DrawContainer* , GameObjectContainer* )>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++) {
		if (it->first == properties["iType"]) {
			auto function = it->second;
			return (this->*function)(properties, container,gameObjectContainer);
		}
	}

	return nullptr;
}


//TODO: Naar de juiste items;
GameObject* ItemFactory::CreatePotion(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer)
{
	std::string imgurl = properties["image"];
	return new Potion(container, imgurl, gameObjectContainer,properties);

}
GameObject* ItemFactory::CreateGun(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer)
{
	return nullptr;
}
GameObject* ItemFactory::CreateAmmo(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer)
{
	return nullptr;
}

GameObject* ItemFactory::CreateKey(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer)
{
	std::string imgurl = properties["image"];
	return new Key(container, imgurl, gameObjectContainer, properties);
}
