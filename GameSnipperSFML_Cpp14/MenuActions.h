#pragma once
#include "BaseInput.h"

namespace Awesomium{
	class WebCore;
	class WebView;
}

class MenuContext;
class StateManager;

class MenuActions : public BaseInput
{
public:
	MenuActions(StateManager* stateManager, MenuContext* menuContext);

	void ExitGame();
	void ReloadPage();
	void ShowAbout();
	void RunGame();
	void ShowIntruction();
	void BackToMenu();

	void NavigateUp();
	void NavigateDown();
	void NavigateComfirm();

	void callDirectJSFunction(Awesomium::WebView* webView, Awesomium::WebCore* web_core, int currentLevel);

	void ProcessActions() override;
	void ExecuteActions() override;
private:
	StateManager* stateManager;
	MenuContext* menuContext;

	std::vector<void(MenuActions::*)()> activeActions;
	std::map<std::string, void(MenuActions::*)()> actions = {
		{ "move-up", &MenuActions::NavigateUp },
		{ "move-down", &MenuActions::NavigateDown },
		{ "enter", &MenuActions::NavigateComfirm },
		{ "escape", &MenuActions::BackToMenu }
	};
};