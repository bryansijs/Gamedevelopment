#pragma once

#include "GameObject.h"

#include <map>

class WeaponFactory
{
public:
	WeaponFactory();
	~WeaponFactory();

	GameObject* Create(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer);
private:
	std::map<std::string, GameObject*(WeaponFactory::*)(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer)> possibleObjects = {
		{ "Pistol", &WeaponFactory::CreatePistol },
		{ "Rifle", &WeaponFactory::CreateRifle }
	};

	GameObject* CreatePistol(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer);
	GameObject* CreateRifle(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer);
};