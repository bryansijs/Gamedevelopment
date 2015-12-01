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
	std::vector<GameObject*>::iterator it;
	for (it = useAbleObjects.begin(); it != useAbleObjects.end(); it++)
	{
		if ((*it) == object)
			break;
	}
	useAbleObjects.erase(it);

}
