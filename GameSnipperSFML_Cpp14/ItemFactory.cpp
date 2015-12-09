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



GameObject* ItemFactory::Create(std::map<std::string, std::string> properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world) {
	std::map<std::string, GameObject*(ItemFactory::*)(std::map<std::string, std::string>&, DrawContainer* , GameObjectContainer*, b2World* )>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++) {
		if (it->first == properties["iType"]) {
			auto function = it->second;
			return (this->*function)(properties, container,gameObjectContainer, world);
		}
	}

	return nullptr;
}


//TODO: Naar de juiste items;
GameObject* ItemFactory::CreatePotion(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world)
{
	std::string imgurl = properties["image"];
	return new Potion(container, imgurl, gameObjectContainer,properties,world);

}
GameObject* ItemFactory::CreateGun(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world)
{
	return nullptr;
}
GameObject* ItemFactory::CreateAmmo(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world)
{
	return nullptr;
}

GameObject* ItemFactory::CreateKey(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world)
{
	std::string imgurl = properties["image"];
	return new Key(container, imgurl, gameObjectContainer, properties,world);
}
