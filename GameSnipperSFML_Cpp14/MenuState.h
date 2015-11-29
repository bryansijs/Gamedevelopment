#pragma once
#include "BaseState.h"
#include <Awesomium/WebCore.h>
#include <map>

class LevelManager;
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
	void ShowLevels();
	void CallLevelEditMenuFunction(Awesomium::WebView* webView, Awesomium::WebCore* web_core, std::string action);

	StateManager* stateManager;
	LevelManager* levelManager;

	Context* context;
	MenuContext* menuContext;

public:
	void Update();
	void Terminate();
	
	void BackToMenu();

	std::map<int, void(MenuState::*)()> menuItems{
		{ 1, &MenuState::RunGame },
		{ 2, &MenuState::ShowLevels },
		{ 3, &MenuState::ShowIntruction },
		{ 4, &MenuState::ShowAbout }
	};

	MenuState(Context* context, StateManager* stateManager, LevelManager* levelmanager);
	~MenuState();
};