#pragma once
#include <iostream>
#include <string>
#include  <memory>
#include <json\json.h>
#include <map>
#include "GameTileFactory.h"
#include "EnemyFactory.h"
#include "ItemFactory.h"
#include "InteractiveFactory.h"
class GameObject;
class DrawContainer;

class GameObjectFactory
{
private:

	DrawContainer *drawContainer;
	MoveContainer *moveContainer;
	std::map<std::string, GameObject*(GameObjectFactory::*)(std::map<std::string, std::string>&)> possibleObjects = {
		{ "Enemy", &GameObjectFactory::CreateEnemy },
		{ "Object", &GameObjectFactory::CreateObject },
		{ "GameTile", &GameObjectFactory::CreateTile },
		{ "Item", &GameObjectFactory::CreateItem },
	};

	GameObject* CreateEnemy(std::map<std::string, std::string>& properties);
	GameObject* CreateObject(std::map<std::string, std::string>&properties);
	GameObject* CreateTile(std::map<std::string, std::string>& properties);
	GameObject* CreateItem(std::map<std::string, std::string>& properties);

	GameTileFactory gametTileFactory;
	EnemyFactory enemyFactory;
	InteractiveFactory interactiveFactory;
	ItemFactory itemFactory;


public:
	GameObjectFactory(DrawContainer *drawContainer);
	GameObjectFactory(DrawContainer *drawContainer, MoveContainer* moveContainer);
	GameObjectFactory();
	~GameObjectFactory();

	GameObject* Create(std::map<std::string, std::string>&);

	void setDrawContainer(DrawContainer* drawContainer) { this->drawContainer = drawContainer; };
	void setMoveContainer(MoveContainer* moveContainer) { this->moveContainer = moveContainer; };

	static GameObjectFactory& getInstance()
	{
		static GameObjectFactory    instance; 			
		return instance;
	}

	GameObjectFactory(GameObjectFactory const&) = delete;
	void operator=(GameObjectFactory const&) = delete;
};

