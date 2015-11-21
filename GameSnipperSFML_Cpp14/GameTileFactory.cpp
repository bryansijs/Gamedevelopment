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

GameObject* GameTileFactory::Create(std::map<std::string, std::string> properties) {
	std::map<std::string, GameObject*(GameTileFactory::*)(std::map<std::string, std::string>)>::iterator  it;
	for (it = possibleTiles.begin(); it != possibleTiles.end(); it++) {
		if (it->first == properties["sType"]) {
			auto function = it->second;
			return (this->*function)(properties);
		}
	}
}

GameObject* GameTileFactory::CreateStart(std::map<std::string, std::string> properties) {
	GameObject* obj = new StartTile();
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	obj->setPosition(sf::Vector2f(x, y));
	return obj;
}

GameObject* GameTileFactory::CreateEnd(std::map<std::string, std::string> properties) {
	GameObject* obj = new EndTile();
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	obj->setPosition(sf::Vector2f(x, y));
	return obj;
}

GameObject* GameTileFactory::CreateWarp(std::map<std::string, std::string> properties) {
	GameObject* obj = new WarpTile();
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	obj->setPosition(sf::Vector2f(x, y));
	return obj;
}
