#include "stdafx.h"
#include "Pistol.h"

#include "GameObjectContainer.h"

Pistol::Pistol(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer) : Gun{ gameObjectContainer }
{
	this->name = "pistol";
	this->fireRate = 0.5f;
}

Pistol::~Pistol()
{
}
