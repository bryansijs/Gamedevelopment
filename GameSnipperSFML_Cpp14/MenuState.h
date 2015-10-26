#pragma once
#include "application.h"
#include "view.h"
#include <iostream>
#include <Awesomium/STLHelpers.h>
#include "BaseState.h"

class StateManager;

namespace Awesomium{
	class WebView;
	class JSArray;
}

class Context;
class MenuState : public BaseState
{	
	Context* context;
	StateManager* stateManager;
public:
	void Terminate();
	void Run();
	MenuState(Context* context, StateManager* stateManager);
	~MenuState();
};

