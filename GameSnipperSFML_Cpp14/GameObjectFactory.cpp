#include "stdafx.h"
#include "GameObjectFactory.h"
#include "GameObject.h"

GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::GameObjectFactory(DrawContainer *drawContainer)
{
	this->drawContainer = drawContainer;
	this->moveContainer = nullptr;
}

GameObjectFactory::GameObjectFactory(DrawContainer *drawContainer, MoveContainer* moveContainer)
{
	this->drawContainer = drawContainer;
	this->moveContainer = moveContainer;
}

GameObjectFactory::~GameObjectFactory()
{
}

GameObject* GameObjectFactory::Create(std::map<std::string, std::string>& properties) {

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
return	this->enemyFactory.Create(properties, drawContainer, moveContainer);
}

GameObject* GameObjectFactory::CreateObject(std::map<std::string, std::string>& properties)
{
	//TODO Andy:drawcontainer & movecontainer & ObjectFactory
	return new GameObject();
}

GameObject* GameObjectFactory::CreateTile(std::map<std::string, std::string>& properties)
{
	return  this->gametTileFactory.Create(properties);
}