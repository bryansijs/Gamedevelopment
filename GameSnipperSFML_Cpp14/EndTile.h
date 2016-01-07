#pragma once
#include "GameObject.h"
#include "Context.h"
#include "StateManager.h"
#include "LevelManager.h"

class ScoreManager;

class EndTile : public GameObject
{
public:
	EndTile(GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, b2World* world);
	~EndTile();

	virtual void setProperties(std::map<std::string, std::string>& properties);
	virtual void doAction();
	
	virtual void startContact(b2Fixture* fixture);
	virtual void endContact(b2Fixture* fixture);
	void setContext(Context* context, StateManager* stateManager, LevelManager* levelManager, ScoreManager* scoreManager);

private:
	Context* context;
	StateManager* stateManager;
	LevelManager* levelManager;
	ScoreManager* scoreManager;
};

