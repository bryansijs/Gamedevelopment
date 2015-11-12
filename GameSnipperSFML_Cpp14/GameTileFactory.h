#pragma once
#include <map>
#include <iostream>
#include <string>
#include  <memory>

class GameObject;
class StartTile;
class WarpTile;
class EndTile;


class GameTileFactory
{
public:
	GameTileFactory();
	~GameTileFactory();

	GameObject* Create(std::map<std::string, std::string> properties);

	std::map<std::string, GameObject*(GameTileFactory::*)(std::map<std::string, std::string>)> possibleTiles = {
		{ "StartTile", &GameTileFactory::CreateStart },
		{ "Warp", &GameTileFactory::CreateWarp },
		{ "End", &GameTileFactory::CreateEnd },
	};
private:
	GameObject* CreateStart(std::map<std::string, std::string> properties);
	GameObject* CreateWarp(std::map<std::string, std::string>properties);
	GameObject* CreateEnd(std::map<std::string, std::string> properties);

};

