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

GameObject* EnemyFactory::Create(std::map<std::string, std::string> properties, DrawContainer* container, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, b2World* world) {
	std::map<std::string, GameObject*(EnemyFactory::*)(std::map<std::string, std::string>&, DrawContainer* , MoveContainer* ,GameObjectContainer*, b2World* )>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++) {
		if (it->first == properties["eType"]) {
			auto function = it->second;
			return (this->*function)(properties, container, mContainer, gameObjectContainer, world);
		}
	}
	return nullptr;
}


GameObject* EnemyFactory::CreateBasic(std::map<std::string, std::string>& properties, DrawContainer* container, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, b2World* world)
{
	std::string imgurl = (properties.count("image")) ?  properties["image"] : "basic.png";

	if (!properties.count("image"))
	{
		properties["width"] = std::to_string(0);
		properties["heigth"] = std::to_string(0);
	}
	
	return new BasicEnemy(container, imgurl, mContainer, gameObjectContainer, properties, world);

}

GameObject* EnemyFactory::CreateRunner(std::map<std::string, std::string>&properties, DrawContainer* container, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, b2World* world) {
	std::string imgurl = (properties.count("image")) ? properties["image"] : "runner.png";

	if (!properties.count("image"))
	{
		properties["width"] = std::to_string(0);
		properties["heigth"] = std::to_string(0);
	}

	return new RunnerEnemy(container, imgurl, mContainer, gameObjectContainer, properties, world);

}

GameObject* EnemyFactory::CreateTank(std::map<std::string, std::string>& properties, DrawContainer* container, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, b2World* world) {
	std::string imgurl = (properties.count("image")) ? properties["image"] : "tank.png";

	if (!properties.count("image"))
	{
		properties["width"] = std::to_string(0);
		properties["heigth"] = std::to_string(0);
	}

	return new TankEnemy(container, imgurl, mContainer, gameObjectContainer, properties, world);

}