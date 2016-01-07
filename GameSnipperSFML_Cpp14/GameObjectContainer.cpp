#include "stdafx.h"
#include "GameObjectContainer.h"


GameObjectContainer::GameObjectContainer()
{
}


GameObjectContainer::~GameObjectContainer()
{
}

void GameObjectContainer::Update()
{
	for (size_t i = 0; i < useAbleObjects.size(); i++)
	{
		if (useAbleObjects.at(i) != nullptr)
			useAbleObjects.at(i)->Update();
	}
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
		{
			useAbleObjects.erase(it);
			break;
		}
	}
}
