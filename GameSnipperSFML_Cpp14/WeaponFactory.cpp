#include "stdafx.h"
#include "WeaponFactory.h"

#include "ProjectileFactory.h"
#include "Pistol.h"
#include "Rifle.h"

WeaponFactory::WeaponFactory()
{
}

WeaponFactory::~WeaponFactory()
{
}

GameObject* WeaponFactory::Create(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer)
{
	std::map<std::string, GameObject*(WeaponFactory::*)(std::map<std::string, std::string>&, GameObjectContainer* gameObjectContainer)>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++)
	{
		if (it->first == properties["wType"])
		{
			auto function = it->second;
			return (this->*function)(properties, gameObjectContainer);
		}
	}

	return nullptr;
}

GameObject* WeaponFactory::CreatePistol(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer)
{
	Pistol* pistol = new Pistol(properties, gameObjectContainer);

	ProjectileFactory projectileFactory;
	std::map<std::string, std::string> bulletProperties = {
		{ "pType", "Bullet" },
		{ "texture", "bullet-red.png" }
	};
	pistol->SetProjectileType(properties["pType"]);

	return pistol;
}

GameObject* WeaponFactory::CreateRifle(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer)
{
	Rifle* rifle = new Rifle(properties, gameObjectContainer);

	ProjectileFactory projectileFactory;
	std::map<std::string, std::string> bulletProperties = {
		{ "pType", "Bullet" },
		{ "texture", "bullet-red.png" }
	};
	rifle->SetProjectileType(properties["pType"]);

	return rifle;
}