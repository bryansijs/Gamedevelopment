#include "stdafx.h"
#include "EnemyFactory.h"
#include "BasicEnemy.h"
#include "RunnerEnemy.h"
#include "TankEnemy.h"

EnemyFactory::EnemyFactory()
{
}


EnemyFactory::~EnemyFactory()
{
}

GameObject* EnemyFactory::Create(std::map<std::string, std::string> properties, DrawContainer* container, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer) {
	std::map<std::string, GameObject*(EnemyFactory::*)(std::map<std::string, std::string>&, DrawContainer* , MoveContainer* ,GameObjectContainer* )>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++) {
		if (it->first == properties["eType"]) {
			auto function = it->second;
			return (this->*function)(properties,container, mContainer, gameObjectContainer);
		}
	}
	return nullptr;
}


GameObject* EnemyFactory::CreateBasic(std::map<std::string, std::string>& properties, DrawContainer* container, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer)
{
	std::string imgurl = properties["image"];
	

	return new BasicEnemy(container, imgurl, mContainer, gameObjectContainer, properties);
}

GameObject* EnemyFactory::CreateRunner(std::map<std::string, std::string>&properties, DrawContainer* container, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer) {
	std::string imgurl = properties["image"];

	return new RunnerEnemy(container, imgurl, mContainer, gameObjectContainer, properties);
}

GameObject* EnemyFactory::CreateTank(std::map<std::string, std::string>& properties, DrawContainer* container, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer) {
	std::string imgurl = properties["image"];


	return new TankEnemy(container, imgurl, mContainer, gameObjectContainer, properties);
}