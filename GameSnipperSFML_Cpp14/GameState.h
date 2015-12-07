#pragma once
#include "BaseState.h"
#include "LevelManager.h"
#include "PlayerActions.h"

class StateManager;
class Context;
class GameContext;
class GameActions;

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

	PlayerActions playerActions;
	GameActions* gameActions;
};

