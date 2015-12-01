#pragma once
#include "BaseState.h"
#include "LevelManager.h"

class StateManager;
class Context;
class GameContext;

class GameState: public BaseState
{
private:
	StateManager* stateManager;
	LevelManager* levelManager;
	Context* maincontext;
	GameContext* gameContext;


public:
	bool isPause = false;
	void Update();
	void Terminate();
	void StartNextLevel();
	
	GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager);
	~GameState();
};

