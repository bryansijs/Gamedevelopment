#include "stdafx.h"
#include "GameTileFactory.h"
#include "StartTile.h"
#include "EndTile.h"
#include "WarpTile.h"

GameTileFactory::GameTileFactory()
{
}


GameTileFactory::~GameTileFactory()
{
}

GameObject* GameTileFactory::Create(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer) {
	std::map<std::string, GameObject*(GameTileFactory::*)(std::map<std::string, std::string>&, GameObjectContainer*)>::iterator  it;
	for (it = possibleTiles.begin(); it != possibleTiles.end(); it++) {
		if (it->first == properties["sType"]) {
			auto function = it->second;
			return (this->*function)(properties, gameObjectContainer);
		}
	}

	return nullptr;
}

GameObject* GameTileFactory::CreateStart(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer) {
	GameObject* obj = new StartTile(gameObjectContainer);
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	obj->setPosition(x, y);
	return obj;
}

GameObject* GameTileFactory::CreateEnd(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer) {
	GameObject* obj = new EndTile(gameObjectContainer);
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	obj->setPosition(x, y);
	return obj;
}

GameObject* GameTileFactory::CreateWarp(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer) {
	GameObject* obj = new WarpTile(gameObjectContainer);
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	obj->setPosition(x, y);
	return obj;
}
