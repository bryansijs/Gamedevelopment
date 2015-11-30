#pragma once
#include <map>
#include <string>
#include  <memory>
#include "GameObject.h"

class GameObject;

class ItemFactory
{
public:
	ItemFactory();
	~ItemFactory();

	GameObject* Create(std::map<std::string, std::string> properties, DrawContainer* container, GameObjectContainer* gameObjectContainer);
private:
	GameObject* CreatePotion(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer);
	GameObject* CreateGun(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer);
	GameObject* CreateAmmo(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer);
	GameObject* CreateKey(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer);

	std::map<std::string, GameObject*(ItemFactory::*)(std::map<std::string, std::string>&, DrawContainer* , GameObjectContainer* )> possibleObjects = {
		{ "Potion", &ItemFactory::CreatePotion },
		{ "Gun", &ItemFactory::CreateGun },
		{ "Ammo", &ItemFactory::CreateAmmo },
	{ "Key", &ItemFactory::CreateKey }, };
};


