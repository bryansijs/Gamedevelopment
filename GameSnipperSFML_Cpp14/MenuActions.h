#pragma once
#include "BaseInput.h"
#include "LevelManager.h"
#include "ScoreManager.h"

namespace Awesomium{
	class WebCore;
	class WebView;
}

class MenuContext;
class StateManager;

class MenuActions : public BaseInput
{
public:
	MenuActions(StateManager* stateManager, MenuContext* menuContext, LevelManager* levelManager, ScoreManager* scoreManager);

	void ExitGame();
	void ReloadPage();
	void ShowAbout();
	void RunGame();
	void ShowIntruction();
	void ShowHighscore();
	void BackToMenu();
	void ShowLevels();

	void NavigateUp();
	void NavigateDown();
	void NavigateLeft();
	void NavigateRight();
	void NavigateComfirm();

	void SwitchToUp();
	void SwitchToDown();

	void addHighScoreToMenu(Awesomium::WebView* webView, Awesomium::WebCore* web_core, const char* naam, int score);
	void addLevelToMenu(Awesomium::WebView* webView, Awesomium::WebCore* web_core, const char* naam);
	void callDirectJSFunction(Awesomium::WebView* webView, Awesomium::WebCore* web_core, int currentLevel);
	void CallLevelEditMenuFunction(Awesomium::WebView* webView, Awesomium::WebCore* web_core, std::string action);

	void ProcessActions();
	void ExecuteActions();
private:
	StateManager* stateManager;
	MenuContext* menuContext;
	LevelManager* levelManager;
	ScoreManager* scoreManager;

	std::map<int, void(MenuActions::*)()> menuItems {
		{ 1, &MenuActions::RunGame },
		{ 2, &MenuActions::ShowLevels },
		{ 3, &MenuActions::ShowIntruction },
		{ 4, &MenuActions::ShowHighscore },
		{ 5, &MenuActions::ShowAbout },
		{ 6, &MenuActions::ExitGame }
	};

	std::vector<void(MenuActions::*)()> activeActions;
	std::map<std::string, void(MenuActions::*)()> actions = {
		{ "move-up", &MenuActions::NavigateUp },
		{ "move-down", &MenuActions::NavigateDown },
		{ "move-left", &MenuActions::NavigateLeft },
		{ "move-right", &MenuActions::NavigateRight },
		{ "switch-up", &MenuActions::SwitchToUp },
		{ "switch-down", &MenuActions::SwitchToDown },
		{ "enter", &MenuActions::NavigateComfirm },
		{ "escape", &MenuActions::BackToMenu }
	};
};