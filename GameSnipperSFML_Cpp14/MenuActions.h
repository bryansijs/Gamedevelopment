#pragma once

namespace Awesomium{
	class WebCore;
	class WebView;
}

class MenuContext;
class StateManager;

class MenuActions
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
private:
	StateManager* stateManager;
	MenuContext* menuContext;
};