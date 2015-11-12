#pragma once
#include <iostream>
#include <string>
#include  <memory>
#include <json\json.h>
#include <map>
#include "GameTileFactory.h"

class GameObject;
class DrawContainer;


class GameObjectFactory
{
private:

	//TODO Singleton Patterns for getInstance;
	DrawContainer *drawContainer;

	std::map<std::string, GameObject*(GameObjectFactory::*)(std::map<std::string, std::string>&)> possibleObjects = {
		{ "Enemy", &GameObjectFactory::CreateEnemy },
		{ "Object", &GameObjectFactory::CreateObject },
		{ "GameTile", &GameObjectFactory::CreateTile },
	};

	GameObject* CreateEnemy(std::map<std::string,std::string>& properties);
	GameObject* CreateObject(std::map<std::string, std::string>&properties);
	GameObject* CreateTile(std::map<std::string, std::string>& properties);

public:
	GameObjectFactory(DrawContainer *drawContainer);
	GameObjectFactory();
	~GameObjectFactory();

	GameObject* Create(std::map<std::string, std::string>);

	GameTileFactory fac;

};

