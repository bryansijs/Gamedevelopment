#pragma once
#include "BaseState.h"
#include <Awesomium/WebCore.h>

class StateManager;
class Context;
class LoseContext;

class LoseState : public BaseState
{
private:
	void ReloadPage();

	StateManager* stateManager;

	Context* context;
	LoseContext* loseContext;
public:
	LoseState(Context* context, StateManager* stateManager);
	~LoseState();

	void Update();
	void ToMenu();
};

