#pragma once
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
	void ShowIntruction();
	void RunGame();
	void ShowAbout();
	void Run();

	MenuState(Context* context, StateManager* stateManager);
	~MenuState();
};