#pragma once
#include "BaseState.h"

class StateManager;
class Context;
class GameContext;

class GameState: public BaseState
{
private:
	StateManager* stateManager;

	GameContext* gameContext;
public:
	void Update();
	void Terminate();

	GameState(Context* context, StateManager* stateManager);
	~GameState();
};

