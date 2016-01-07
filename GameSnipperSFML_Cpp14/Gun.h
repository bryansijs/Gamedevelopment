#pragma once

#include "BaseItem.h"
#include <iostream>

class Gun : public BaseItem
{
public:
	Gun(GameObjectContainer* gameObjectContainer);
	~Gun();

	std::string GetProjectileType();
	void SetProjectileType(std::string projectileType);

	float GetFireRate();
	void SetFireRate(float fireRate);

	std::string GetName() { return name; };
private:
	std::string projectileType;
protected:
	std::string name;
	float fireRate = 0.5f;
};