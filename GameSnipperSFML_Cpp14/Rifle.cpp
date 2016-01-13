#include "stdafx.h"
#include "Rifle.h"

Rifle::Rifle(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer) : Gun{ gameObjectContainer }
{
	this->name = "rifle";
	this->bulletTexture = "bullet-blue.png";
	this->fireRate = 0.1f;
	this->damage = 5;
}

Rifle::~Rifle()
{
}
