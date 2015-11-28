#pragma once
#include "BaseState.h"
#include <Awesomium/WebCore.h>

class StateManager;
class Context;
class MenuContext;

class MenuState : public BaseState
{
private:
	void ReloadPage();
	void ShowAbout();
	void RunGame();
	void ShowIntruction();

	StateManager* stateManager;

	Context* context;
	MenuContext* menuContext;
public:
	void Update() override;
	void Terminate() override;

	void BackToMenu();

	std::map <int, void(MenuState::*)()> menuItems{
		{ 1, &MenuState::RunGame },
		{ 2, &MenuState::ShowIntruction },
		{ 3, &MenuState::ShowAbout }
	};

	MenuState(Context* context, StateManager* stateManager);
	~MenuState();

	static void callDirectJSFunction(Awesomium::WebView* webView, Awesomium::WebCore* web_core, int currentLevel);
};