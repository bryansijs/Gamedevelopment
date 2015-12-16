#include "stdafx.h"
#include "GameTileFactory.h"
#include "StartTile.h"
#include "EndTile.h"
#include "WarpTile.h"
#include "StoryTile.h"
#include <Box2D\Box2D.h>

GameTileFactory::GameTileFactory()
{
}


GameTileFactory::~GameTileFactory()
{
}

GameObject* GameTileFactory::Create(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer, b2World* world) {
	std::map<std::string, GameObject*(GameTileFactory::*)(std::map<std::string, std::string>&, GameObjectContainer*, b2World* )>::iterator  it;
	for (it = possibleTiles.begin(); it != possibleTiles.end(); it++) {
		if (it->first == properties["sType"]) {
			auto function = it->second;
			return (this->*function)(properties, gameObjectContainer, world);
		}
	}

	return nullptr;
}

GameObject* GameTileFactory::CreateStart(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer, b2World* world) {
	GameObject* obj = new StartTile(gameObjectContainer);
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	obj->setPosition(x, y);
	return obj;
}

GameObject* GameTileFactory::CreateEnd(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer, b2World* world) {
	GameObject* obj = new EndTile(gameObjectContainer, properties, world);
	return obj;
}

GameObject* GameTileFactory::CreateWarp(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer, b2World* world) {
	GameObject* obj = new WarpTile(gameObjectContainer);
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	obj->setPosition(x, y);
	return obj;
}

GameObject* GameTileFactory::CreateStory(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer, b2World* world) {
	GameObject* obj = new StoryTile(gameObjectContainer, properties, world);
	return obj;
}

GameObject * GameTileFactory::CreateDiscovery(std::map<std::string, std::string>& properties, GameObjectContainer * gameObjectContainer, b2World * world)
{
	return nullptr;
}
