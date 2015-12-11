#pragma once
#include "GameObject.h"
class StoryTile : public GameObject
{
public:
	StoryTile(GameObjectContainer * gameObjectContainer);
	~StoryTile();

	virtual void setProperties(std::map<std::string, std::string>& properties);
	virtual void doAction();

	virtual void startContact(b2Fixture* fixture);
	virtual void endContact(b2Fixture* fixture);
private:
	bool told = false;
};

