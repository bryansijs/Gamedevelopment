#pragma once

#include "GameObject.h"

#include <map>

class ProjectileFactory
{
public:
	ProjectileFactory();
	~ProjectileFactory();

	GameObject* Create(std::map<std::string, std::string>& properties, DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world);
private:
	std::map<std::string, GameObject*(ProjectileFactory::*)(std::map<std::string, std::string>& properties, DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world)> possibleObjects = {
		{ "Bullet", &ProjectileFactory::CreateBullet }
	};

	GameObject* CreateBullet(std::map<std::string, std::string>& properties, DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world);
};