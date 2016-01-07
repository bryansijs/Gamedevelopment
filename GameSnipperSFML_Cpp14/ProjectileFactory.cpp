#include "stdafx.h"
#include "ProjectileFactory.h"

#include "Bullet.h"

#include "DrawContainer.h"
#include "GameObjectContainer.h"

ProjectileFactory::ProjectileFactory()
{
}

ProjectileFactory::~ProjectileFactory()
{
}

GameObject* ProjectileFactory::Create(std::map<std::string, std::string>& properties, DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world)
{
	std::map<std::string, GameObject*(ProjectileFactory::*)(std::map<std::string, std::string>&, DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World*)>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++)
	{
		if (it->first == properties["pType"])
		{
			auto function = it->second;
			return (this->*function)(properties, drawContainer, moveContainer, gameObjectContainer, world);
		}
	}

	return nullptr;
}

GameObject* ProjectileFactory::CreateBullet(std::map<std::string, std::string>& properties, DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world)
{
	return new Bullet(gameObjectContainer, properties, world, moveContainer, drawContainer, properties["texture"]);
}