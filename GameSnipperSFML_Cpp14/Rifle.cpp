#include "stdafx.h"
#include "Rifle.h"

Rifle::Rifle(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer) : Gun{ gameObjectContainer }
{
	this->fireRate = 0.1f;
}

Rifle::~Rifle()
{
}
