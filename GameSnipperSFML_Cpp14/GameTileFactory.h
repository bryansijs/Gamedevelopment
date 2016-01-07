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
class b2World;
class Level;
class GameTileFactory
{
public:
	GameTileFactory();
	~GameTileFactory();

	GameObject* Create(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer, b2World* world, Level* level);
private:
	GameObject* CreateStart(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer, b2World* world);
	GameObject* CreateWarp(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer, b2World* world);
	GameObject* CreateEnd(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer, b2World* world);
	GameObject* CreateStory(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer, b2World* world);
	GameObject* CreateDiscovery(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer, b2World* world);

	std::map<std::string, GameObject*(GameTileFactory::*)(std::map<std::string, std::string>&,  GameObjectContainer*, b2World*)> possibleTiles = {
		{ "StartTile", &GameTileFactory::CreateStart },
		{ "Warp", &GameTileFactory::CreateWarp },
		{ "End", &GameTileFactory::CreateEnd },
		{ "StoryTile", &GameTileFactory::CreateStory },
		{ "DiscoverTile", &GameTileFactory::CreateDiscovery },
	};

	Level* level;
};

