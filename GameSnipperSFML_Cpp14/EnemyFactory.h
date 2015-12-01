#pragma once

#include <map>
#include <string>
#include  <memory>
#include "GameObject.h"

class EnemyFactory
{
public:
	EnemyFactory();
	~EnemyFactory();
	GameObject* Create(std::map<std::string, std::string> properties, DrawContainer* container, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, b2World* world);

private:
	std::map<std::string, GameObject*(EnemyFactory::*)(std::map<std::string, std::string>&, DrawContainer* , MoveContainer* ,GameObjectContainer*, b2World* world)> possibleObjects = {
		{ "Basic", &EnemyFactory::CreateBasic },
		{ "Runner", &EnemyFactory::CreateRunner },
		{ "Tank", &EnemyFactory::CreateTank },
	};

	GameObject* CreateBasic(std::map<std::string, std::string>& properties, DrawContainer* container, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, b2World* world);
	GameObject* CreateRunner(std::map<std::string, std::string>&properties, DrawContainer* container, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, b2World* world);
	GameObject* CreateTank(std::map<std::string, std::string>& properties, DrawContainer* container, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, b2World* world);
};

