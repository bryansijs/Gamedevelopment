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

	GameObject* Create(std::map<std::string, std::string> properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world);
private:
	GameObject* CreatePotion(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world);
	GameObject* CreateGun(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world);
	GameObject* CreateAmmo(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer, b2World* world);
	GameObject* CreateKey(std::map<std::string, std::string>& properties, DrawContainer* container, GameObjectContainer* gameObjectContainer,b2World* world);

	std::map<std::string, GameObject*(ItemFactory::*)(std::map<std::string, std::string>&, DrawContainer* , GameObjectContainer*, b2World* )> possibleObjects = {
		{ "Potion", &ItemFactory::CreatePotion },
		{ "Gun", &ItemFactory::CreateGun },
		{ "Ammo", &ItemFactory::CreateAmmo },
	{ "Key", &ItemFactory::CreateKey }, };
};


