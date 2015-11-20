#pragma once
#include <vector>

#include "GameObject.h"

class UseContainer
{
public:
	UseContainer();
	~UseContainer();

	void AddObject(GameObject* object);
	void RemoveObject(GameObject* object);
	std::vector<GameObject*> getObjects() { return useAbleObjects; }
private:
	std::vector<GameObject*> useAbleObjects;
};

