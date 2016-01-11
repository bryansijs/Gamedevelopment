#include "stdafx.h"
#include "Gun.h"

#include "GameObjectContainer.h"

Gun::Gun(GameObjectContainer* gameObjectContainer)
{
	gameObjectContainer->AddObject(this);
}

Gun::~Gun()
{
}

std::string Gun::GetProjectileType()
{
	return this->projectileType;
}

void Gun::SetProjectileType(std::string projectileType)
{
	this->projectileType = projectileType;
}

int Gun::GetDamage()
{
	return this->damage;
}

float Gun::GetFireRate()
{
	return this->fireRate;
}

void Gun::SetFireRate(float fireRate)
{
	this->fireRate = fireRate;
}
