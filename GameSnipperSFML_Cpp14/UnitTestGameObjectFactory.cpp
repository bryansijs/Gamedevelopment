#include "stdafx.h"
#include "UnitTestGameObjectFactory.h"
#include "UnitTest.h"
#include "GameObject.h";
#include "GameObjectFactory.h"
#include "EndTile.h"
#include "RunnerEnemy.h"
#include "TankEnemy.h"
#include "StartTile.h"
#include "BasicEnemy.h"
#include "DrawContainer.h"
#include "MoveContainer.h"
#include "Potion.h"
#include "Door.h"
#include "Key.h"
UnitTestGameObjectFactory::UnitTestGameObjectFactory()
{
	DrawContainer* cont = new DrawContainer();
	MoveContainer* move = new MoveContainer();
	GameObjectFactory factory{ cont,move };

	std::map<std::string, std::string> propertymap;
	propertymap.insert(std::pair<std::string, std::string>("image", "player.png"));
	propertymap.insert(std::pair<std::string, std::string>("type", "GameTile"));
	propertymap.insert(std::pair<std::string, std::string>("sType", "StartTile"));
	propertymap.insert(std::pair<std::string, std::string>("x", "20"));
	propertymap.insert(std::pair<std::string, std::string>("y", "20"));
	propertymap.insert(std::pair<std::string, std::string>("width", "20"));
	propertymap.insert(std::pair<std::string, std::string>("height", "20"));

	GameObject* object = factory.Create(propertymap);
	UnitTest::Compare("Tile is a startile: ", dynamic_cast<StartTile*>(object), true);
	UnitTest::Compare("Tile not is a endTile: ", dynamic_cast<EndTile*>(object), false);

	propertymap.clear();
	object->~GameObject();
	propertymap.insert(std::pair<std::string, std::string>("image", "player.png"));
	propertymap.insert(std::pair<std::string, std::string>("type", "Enemy"));
	propertymap.insert(std::pair<std::string, std::string>("eType", "Runner"));
	propertymap.insert(std::pair<std::string, std::string>("x", "20"));
	propertymap.insert(std::pair<std::string, std::string>("y", "20"));
	propertymap.insert(std::pair<std::string, std::string>("width", "20"));
	propertymap.insert(std::pair<std::string, std::string>("height", "20"));
	object = factory.Create(propertymap);

	UnitTest::Compare("Enemy is a runner: ", dynamic_cast<RunnerEnemy*>(object), true);
	UnitTest::Compare("Enemy is not a basic: ", dynamic_cast<BasicEnemy*>(object), false);
	propertymap.clear();
	object->~GameObject();
	propertymap.insert(std::pair<std::string, std::string>("image", "player.png"));
	propertymap.insert(std::pair<std::string, std::string>("type", "Enemy"));
	propertymap.insert(std::pair<std::string, std::string>("eType", "Tank"));
	propertymap.insert(std::pair<std::string, std::string>("x", "20"));
	propertymap.insert(std::pair<std::string, std::string>("y", "20"));
	propertymap.insert(std::pair<std::string, std::string>("width", "20"));
	propertymap.insert(std::pair<std::string, std::string>("height", "20"));

	object = factory.Create(propertymap);
	UnitTest::Compare("Enemy is a Tank: ", dynamic_cast<TankEnemy*>(object), true);
	UnitTest::Compare("Enemy is not a runner: ", dynamic_cast<RunnerEnemy*>(object), false);

	propertymap.clear();
	object->~GameObject();
	propertymap.insert(std::pair<std::string, std::string>("image", "player.png"));
	propertymap.insert(std::pair<std::string, std::string>("type", "Item"));
	propertymap.insert(std::pair<std::string, std::string>("iType", "Potion"));
	propertymap.insert(std::pair<std::string, std::string>("x", "20"));
	propertymap.insert(std::pair<std::string, std::string>("y", "80"));
	propertymap.insert(std::pair<std::string, std::string>("width", "20"));
	propertymap.insert(std::pair<std::string, std::string>("height", "20"));
	
	object = factory.Create(propertymap);
	UnitTest::Compare("Item is a potion: ", dynamic_cast<Potion*>(object), true);
	UnitTest::Compare("Item is not an enemy: ", dynamic_cast<RunnerEnemy*>(object), false);
	UnitTest::Compare("both x are 20: ",int(object->getPosition().x),20);
	UnitTest::Compare("both y are 80: ", int(object->getPosition().y), 80);
	UnitTest::Compare("Vector equals: " ,object->getPosition(), sf::Vector2f(20,80));
	
	propertymap.clear();
	object->~GameObject();
	propertymap.insert(std::pair<std::string, std::string>("image", "player.png"));
	propertymap.insert(std::pair<std::string, std::string>("type", "Object"));
	propertymap.insert(std::pair<std::string, std::string>("iType", "Door"));
	propertymap.insert(std::pair<std::string, std::string>("x", "20"));
	propertymap.insert(std::pair<std::string, std::string>("y", "20"));
	propertymap.insert(std::pair<std::string, std::string>("width", "20"));
	propertymap.insert(std::pair<std::string, std::string>("height", "20"));

	object = factory.Create(propertymap);
	UnitTest::Compare("Object is a door: ", dynamic_cast<Door*>(object), true);
	UnitTest::Compare("Object is not an enemy: ", dynamic_cast<RunnerEnemy*>(object), false);

	propertymap.clear();
	object->~GameObject();
	propertymap.insert(std::pair<std::string, std::string>("image", "player.png"));
	propertymap.insert(std::pair<std::string, std::string>("type", "Item"));
	propertymap.insert(std::pair<std::string, std::string>("iType", "Key"));
	propertymap.insert(std::pair<std::string, std::string>("x", "20"));
	propertymap.insert(std::pair<std::string, std::string>("y", "80"));
	propertymap.insert(std::pair<std::string, std::string>("width", "20"));
	propertymap.insert(std::pair<std::string, std::string>("height", "20"));

	object = factory.Create(propertymap);
	UnitTest::Compare("Item is not a potion: ", dynamic_cast<Potion*>(object), false);
	UnitTest::Compare("Item is a key: ", dynamic_cast<Key*>(object), true);

	propertymap.clear();
	object->~GameObject();
	cont->~DrawContainer();
	move->~MoveContainer();
}


UnitTestGameObjectFactory::~UnitTestGameObjectFactory()
{
}
