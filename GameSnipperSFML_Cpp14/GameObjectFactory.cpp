#include "stdafx.h"
#include "GameObjectFactory.h"
#include "GameObject.h"

GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::GameObjectFactory(DrawContainer *drawContainer, MoveContainer* moveContainer,GameObjectContainer* gameObjectContainer, b2World* world)
{
	this->drawContainer = drawContainer;
	this->moveContainer = moveContainer;
	this->gameObjectContainer = gameObjectContainer;
	this->world = world;
}

GameObjectFactory::~GameObjectFactory()
{
}

GameObject* GameObjectFactory::Create(std::map<std::string, std::string>& properties)
{
	std::map<std::string, GameObject*(GameObjectFactory::*)(std::map<std::string, std::string>&)>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++) {
		if (it->first == properties["type"]) {
			auto function = it->second;
			return (this->*function)(properties);
		}
	}

	return nullptr;
}

GameObject* GameObjectFactory::CreateEnemy(std::map<std::string, std::string>& properties)
{
	return	this->enemyFactory.Create(properties, drawContainer, moveContainer, gameObjectContainer,world);
}

GameObject* GameObjectFactory::CreateObject(std::map<std::string, std::string>& properties)
{
	return this->interactiveFactory.Create(properties, drawContainer, gameObjectContainer,world, this->tileList);
}

GameObject* GameObjectFactory::CreateTile(std::map<std::string, std::string>& properties)
{
	return  this->gametTileFactory.Create(properties, gameObjectContainer, world);
}

GameObject* GameObjectFactory::CreateItem(std::map<std::string, std::string>& properties)
{
	return this->itemFactory.Create(properties, drawContainer, gameObjectContainer,world);
}