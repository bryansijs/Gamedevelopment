#pragma once
#include "GameObject.h"
#include <vector>
#include "Level.h"
class DiscoverTile : public GameObject
{
public:
	DiscoverTile(GameObjectContainer * gameObjectContainer, std::map<std::string, std::string>& properties, b2World * world);
	~DiscoverTile();

	virtual void setProperties(std::map<std::string, std::string>& properties);
	virtual void doAction();

	virtual void startContact(b2Fixture* fixture);
	virtual void endContact(b2Fixture* fixture);

private:
	Level* level;
};

