#include "stdafx.h"
#include "UseContainer.h"


UseContainer::UseContainer()
{
}


UseContainer::~UseContainer()
{
}


void UseContainer::AddObject(GameObject* object)
{
	useAbleObjects.push_back(object);
}

void UseContainer::RemoveObject(GameObject* object)
{
//	useAbleObjects.erase(object);
}
