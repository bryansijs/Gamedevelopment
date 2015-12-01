#pragma once
#include "BaseState.h"
#include "LevelManager.h"

class StateManager;
class Context;
class GameContext;

class GameState: public BaseState
{
public:
	GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager);
	~GameState();

	void Update() override;
	void Terminate() override;
	void StartNextLevel();
private:
	StateManager* stateManager;
	LevelManager* levelManager;
	Context* maincontext;
	GameContext* gameContext;
};

