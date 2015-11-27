#pragma once
#include <map>
#include <iostream>
#include <string>
#include  <memory>

class GameObject;
class GameObjectContainer;
class StartTile;
class WarpTile;
class EndTile;


class GameTileFactory
{
public:
	GameTileFactory();
	~GameTileFactory();

	GameObject* Create(std::map<std::string, std::string>& properties, 
		GameObjectContainer* gameObjectContainer);
private:
	GameObject* CreateStart(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer);
	GameObject* CreateWarp(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer);
	GameObject* CreateEnd(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer);

	std::map<std::string, GameObject*(GameTileFactory::*)(std::map<std::string, std::string>&,  GameObjectContainer*)> possibleTiles = {
		{ "StartTile", &GameTileFactory::CreateStart },
		{ "Warp", &GameTileFactory::CreateWarp },
		{ "End", &GameTileFactory::CreateEnd },
	};
};

