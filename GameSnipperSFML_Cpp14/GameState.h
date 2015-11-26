#pragma once
#include "BaseState.h"

class StateManager;
class Context;
class GameContext;

class GameState: public BaseState
{
public:
	void Update() override;
	void Terminate() override;

	GameState(Context* context, StateManager* stateManager);
	~GameState();
private:
	StateManager* stateManager;
	GameContext* gameContext;
};

