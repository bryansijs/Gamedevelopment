#pragma once
#include "BaseState.h"
#include <Awesomium/WebCore.h>

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
public:
	WinState(Context* context, StateManager* stateManager);
	~WinState();

	void Update();
	void ToMenu();
};

