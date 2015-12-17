#pragma once
#include "GameObject.h"
#include "StorylineManager.h"
#include <vector>

class StoryTile : public GameObject
{
public:
	StoryTile(GameObjectContainer * gameObjectContainer, std::map<std::string, std::string>& properties, b2World * world);
	~StoryTile();

	virtual void setProperties(std::map<std::string, std::string>& properties);
	virtual void doAction();

	virtual void startContact(b2Fixture* fixture);
	virtual void endContact(b2Fixture* fixture);
	void setStorylineManager(StorylineManager* storylineManager);
private:
	bool told = false;
	StorylineManager* storylineManager;
	std::vector<std::string> storys;
};

