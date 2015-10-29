#pragma once
#include "BaseState.h"
#include <Awesomium/WebCore.h>

class StateManager;

namespace Awesomium{
	class WebView;
	class JSArray;
}

class Context;
class MenuState : public BaseState
{
	int currentLevel;
	char const* pathToFile;
	bool inMenu = false;
	Awesomium::WebView* webView;
	Awesomium::WebCore* web_core;
	Context* context;
	StateManager* stateManager;

	void ReloadPage();
	void ShowAbout();
	void RunGame();
	void ShowIntruction();

public:
	void Terminate();
	void BackToMenu();
	void Run();

	MenuState(Context* context, StateManager* stateManager);
	~MenuState();
};