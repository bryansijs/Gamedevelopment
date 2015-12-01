#pragma once
#include "BaseState.h"
#include "MenuActions.h"

class StateManager;
class Context;
class MenuContext;

class MenuState : public BaseState
{
public:
	void Update() override;
	void Terminate() override;

	MenuState(Context* context, StateManager* stateManager);
	~MenuState();
private:
	StateManager* stateManager;
	MenuContext* menuContext;
	MenuActions* menuActions;
};