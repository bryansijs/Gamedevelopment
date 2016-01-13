#pragma once

#include "BaseItem.h"

class Gun : public BaseItem
{
public:
	Gun(GameObjectContainer* gameObjectContainer);
	~Gun();

	std::string GetProjectileType();
	void SetProjectileType(std::string projectileType);

	int GetDamage();

	float GetFireRate();
	void SetFireRate(float fireRate);
	std::string GetBulletTexture() { return bulletTexture; };
	std::string GetName() { return name; };
private:
	std::string projectileType;
protected:
	std::string name;
	std::string bulletTexture;
	int damage = 20;
	float fireRate = 0.5f;
};