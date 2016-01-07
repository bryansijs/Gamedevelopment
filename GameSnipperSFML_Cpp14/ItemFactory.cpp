#include "stdafx.h"
#include "ItemFactory.h"
#include "Potion.h"
#include "Key.h"
#include "Gun.h"
#include "ProjectileFactory.h"

ItemFactory::ItemFactory()
{
}


ItemFactory::~ItemFactory()
{
}



GameObject* ItemFactory::Create(std::map<std::string, std::string> properties, DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world) {
	std::map<std::string, GameObject*(ItemFactory::*)(std::map<std::string, std::string>&, DrawContainer*, MoveContainer*, GameObjectContainer*, b2World* )>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++) {
		if (it->first == properties["iType"]) {
			auto function = it->second;
			return (this->*function)(properties, drawContainer, moveContainer, gameObjectContainer, world);
		}
	}

	return nullptr;
}


//TODO: Naar de juiste items;
GameObject* ItemFactory::CreatePotion(std::map<std::string, std::string>& properties, DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world)
{
	std::string imgurl = properties["image"];
	return new Potion(drawContainer, imgurl, gameObjectContainer,properties,world);

}
GameObject* ItemFactory::CreateAmmo(std::map<std::string, std::string>& properties, DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world)
{
	return nullptr;
}

GameObject* ItemFactory::CreateKey(std::map<std::string, std::string>& properties, DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world)
{
	std::string imgurl = properties["image"];
	return new Key(drawContainer, imgurl, gameObjectContainer, properties,world);
}
