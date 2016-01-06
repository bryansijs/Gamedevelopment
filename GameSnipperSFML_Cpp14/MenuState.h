#pragma once
#include "BaseState.h"
#include "MenuActions.h"

class LevelManager;
class StateManager;
class Context;
class MenuContext;

class MenuState : public BaseState
{
public:
	MenuState(Context* context, StateManager* stateManager, LevelManager* levelmanager, ScoreManager* scoreManager);
	~MenuState();

	void Update() override;
	void Terminate() override;
private:
	LevelManager* levelManager;
	StateManager* stateManager;
	ScoreManager* scoreManager;
	MenuContext* menuContext;
	MenuActions* menuActions;
	Context* context;
};