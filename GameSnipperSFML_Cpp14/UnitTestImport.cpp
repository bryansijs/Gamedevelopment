#include "stdafx.h"
#include "UnitTestImport.h"
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
UnitTestImport::UnitTestImport()
{

	DrawContainer* cont = new DrawContainer();
	MoveContainer* move = new MoveContainer();
	GameObjectFactory factory{ cont,move };

	std::map<std::string, std::string> propertymap;

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

	propertymap.insert(std::pair<std::string, std::string>("type", "Item"));
	propertymap.insert(std::pair<std::string, std::string>("iType", "Potion"));
	propertymap.insert(std::pair<std::string, std::string>("x", "20"));
	propertymap.insert(std::pair<std::string, std::string>("y", "20"));
	propertymap.insert(std::pair<std::string, std::string>("width", "20"));
	propertymap.insert(std::pair<std::string, std::string>("height", "20"));
	
	object = factory.Create(propertymap);
	UnitTest::Compare("Item is a potion: ", dynamic_cast<Potion*>(object), true);
	UnitTest::Compare("Item is not an enemy: ", dynamic_cast<RunnerEnemy*>(object), false);

	propertymap.clear();
	object->~GameObject();

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
	cont->~DrawContainer();
	move->~MoveContainer();

}


UnitTestImport::~UnitTestImport()
{
}
