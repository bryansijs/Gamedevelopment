#pragma once
#include "BaseState.h"
#include <Awesomium/WebCore.h>
#include "LevelManager.h"

class StateManager;
class Context;
class WinContext;

class WinState : public BaseState
{
private:
	void ReloadPage();

	StateManager* stateManager;

	Context* context;
	WinContext* winContext;
	LevelManager* levelManager;
public:
	WinState(Context* context, StateManager* stateManager, LevelManager* levelManager);
	~WinState();

	void Update();
	void ToMenu();
};

