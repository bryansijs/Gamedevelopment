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
private:
	std::string projectileType;
protected:
	float fireRate = 0.5f;
};