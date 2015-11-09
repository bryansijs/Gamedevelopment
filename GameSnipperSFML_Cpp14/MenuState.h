#pragma once
#include "BaseState.h"
#include <Awesomium/WebCore.h>

class StateManager;
class Context;
class MenuContext;

namespace Awesomium{
	class WebView;
	class JSArray;
}

class Context;
class MenuState : public BaseState
{
private:
	void ReloadPage();
	void ShowAbout();
	void RunGame();
	void ShowIntruction();

	StateManager* stateManager;
	MenuContext* menuContext;
public:
	void Create(Context* context);
	void Run();
	void Terminate();

	void BackToMenu();

	MenuState(Context* context, StateManager* stateManager);
	~MenuState();
};