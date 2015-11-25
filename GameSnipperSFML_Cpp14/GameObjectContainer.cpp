#include "stdafx.h"
#include "GameObjectContainer.h"


GameObjectContainer::GameObjectContainer()
{
}


GameObjectContainer::~GameObjectContainer()
{
}


void GameObjectContainer::AddObject(GameObject* object)
{
	useAbleObjects.push_back(object);
}

void GameObjectContainer::RemoveObject(GameObject* object)
{
//	useAbleObjects.erase(object);
}
