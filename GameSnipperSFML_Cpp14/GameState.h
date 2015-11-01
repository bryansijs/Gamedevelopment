#pragma once
#include "BaseState.h"
#include "Context.h"

class StateManager;

class GameState: public BaseState
{
	Context* context;
	StateManager* stateManager;
public:
	void Run();
	void Terminate();
	GameState(Context* context, StateManager* stateManager);
	~GameState();
};

