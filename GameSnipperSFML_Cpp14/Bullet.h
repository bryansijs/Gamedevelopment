#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(GameObjectContainer * gameObjectContainer, std::map<std::string, std::string>& properties, b2World * world, MoveContainer * moveContainer, DrawContainer * drawContainer, std::string texture);
	~Bullet();

	void startContact(b2Fixture* fixture);
	void endContact(b2Fixture* fixture);
};