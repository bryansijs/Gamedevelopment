#include "stdafx.h"
#include "EnemyFactory.h"
#include "BasicEnemy.h"

EnemyFactory::EnemyFactory()
{
}


EnemyFactory::~EnemyFactory()
{
}

GameObject* EnemyFactory::Create(std::map<std::string, std::string> properties, DrawContainer* container, MoveContainer* mContainer) {
	std::map<std::string, GameObject*(EnemyFactory::*)(std::map<std::string, std::string>&, DrawContainer* container, MoveContainer* mContainer)>::iterator  it;
	for (it = possibleObjects.begin(); it != possibleObjects.end(); it++) {
		if (it->first == properties["eType"]) {
			auto function = it->second;
			return (this->*function)(properties,container, mContainer);
		}
	}

	return nullptr;
}


GameObject* EnemyFactory::CreateBasic(std::map<std::string, std::string>& properties, DrawContainer* container, MoveContainer* mContainer)
{
	std::string imgurl = properties["image"];
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);

	return new BasicEnemy(container, imgurl, mContainer, sf::Vector2f(x,y), widht,height);
}


//TODO Andy:Enemy verder uitwerken
GameObject* EnemyFactory::CreateRunner(std::map<std::string, std::string>&properties, DrawContainer* container, MoveContainer* mContainer) {
	std::string imgurl = properties["image"];
	GameObject* obj = new GameObject(container, imgurl);
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);
	obj->setPosition(sf::Vector2f(x, y));
	obj->setSize(widht, height);

	return obj;
}
//TODO Andy:Enemy verder uitwerken
GameObject* EnemyFactory::CreateTank(std::map<std::string, std::string>& properties, DrawContainer* container, MoveContainer* mContainer) {
	std::string imgurl = properties["image"];
	GameObject* obj = new GameObject(container, imgurl);
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);
	obj->setPosition(sf::Vector2f(x, y));
	obj->setSize(widht, height);

	return obj;
}