#include "stdafx.h"
#include "GameObjectFactory.h"
#include "GameObject.h"

GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::GameObjectFactory(DrawContainer *drawContainer)
{
	this->drawContainer = drawContainer;
}

GameObjectFactory::~GameObjectFactory()
{
}
//TODO REF
GameObject* GameObjectFactory::Create(std::map<std::string, std::string> properties) {

	std::map<std::string, GameObject*(GameObjectFactory::*)(std::map<std::string, std::string>&)>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++) {
		if (it->first == properties["type"]) {
			auto function = it->second;
			return (this->*function)(properties);
		}
	}

	return nullptr;
}

//TODO: EnemyFactory
GameObject* GameObjectFactory::CreateEnemy(std::map<std::string, std::string>& properties)
{
	std::string imgurl = properties["image"];
	GameObject* obj = new GameObject(drawContainer, imgurl);
	int x, y, widht, height;
	x = std::stoi( properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);
	obj->setPosition(sf::Vector2f(x, y));
	obj->setSize(widht, height);

	return obj;
}

GameObject* GameObjectFactory::CreateObject(std::map<std::string, std::string>& properties)
{
	return new GameObject();
}

GameObject* GameObjectFactory::CreateTile(std::map<std::string, std::string>& properties)
{
	return  this->fac.Create(properties);
}