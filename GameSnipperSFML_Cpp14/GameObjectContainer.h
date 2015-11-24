#pragma once
#include <vector>

#include "GameObject.h"

class GameObjectContainer
{
public:
	GameObjectContainer();
	~GameObjectContainer();

	void AddObject(GameObject* object);
	void RemoveObject(GameObject* object);
	std::vector<GameObject*> getObjects() { return useAbleObjects; }
private:
	std::vector<GameObject*> useAbleObjects;
};

