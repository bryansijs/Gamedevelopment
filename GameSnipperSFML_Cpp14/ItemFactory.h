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

	GameObject* Create(std::map<std::string, std::string> properties, DrawContainer* container);
private:
	GameObject* CreatePotion(std::map<std::string, std::string>& properties, DrawContainer* container);
	GameObject* CreateGun(std::map<std::string, std::string>& properties, DrawContainer* container);
	GameObject* CreateAmmo(std::map<std::string, std::string>& properties, DrawContainer* container);
	GameObject* CreateKey(std::map<std::string, std::string>& properties, DrawContainer* container);

	std::map<std::string, GameObject*(ItemFactory::*)(std::map<std::string, std::string>&, DrawContainer* container)> possibleObjects = {
		{ "Potion", &ItemFactory::CreatePotion },
		{ "Gun", &ItemFactory::CreateGun },
		{ "Ammo", &ItemFactory::CreateAmmo },
	{ "Key", &ItemFactory::CreateKey }, };
};


