#include "stdafx.h"
#include "MenuActions.h"
#include "StateManager.h"
#include "GameState.h"
#include "MenuContext.h"
#include <Awesomium/STLHelpers.h>
#include "Context.h"
#include "KeyMapping.h"
#include "ScoreManager.h"

using namespace Awesomium;

MenuActions::MenuActions(StateManager* stateManager, MenuContext* menuContext, LevelManager* levelManager,ScoreManager* scoreManager)
{
	MenuActions::stateManager = stateManager;
	MenuActions::menuContext = menuContext;
	MenuActions::levelManager = levelManager;
	MenuActions::scoreManager = scoreManager;
}

void MenuActions::ProcessActions()
{
	map<string, void(MenuActions::*)()>::iterator it;

	for (vector<int>::size_type i = 0; i != activeKeys.size(); i++) {

		string map = KeyMapping::GetMap(activeKeys[i]);

		for (it = actions.begin(); it != actions.end(); ++it)
		{
			if (map.find(it->first) != string::npos)
			{
				if (find(activeActions.begin(), activeActions.end(), it->second) == activeActions.end())
				{
					activeActions.push_back(it->second);
				}
			}
		}
	}
	ExecuteActions();
}

void MenuActions::ExecuteActions()
{
	std::vector<void(MenuActions::*)()>::iterator it;
	for (it = activeActions.begin(); it != activeActions.end(); ++it)
	{
		auto function = *it;
		(this->*function)();
	}
	activeActions.clear();
}

void MenuActions::ExitGame()
{
	menuContext->context->window.close();
	stateManager->PopState();
}

void MenuActions::RunGame()
{
	menuContext->music->stop();
	GameState* gameState = new GameState(menuContext->context, stateManager, levelManager, scoreManager);
	stateManager->AddState(gameState);
	stateManager->StartNextState();
}

void MenuActions::ShowAbout()
{
	menuContext->inMenu = false;
	menuContext->pathToFile = "file:///Resources/menuHTML/about.html";
	ReloadPage();
}

void MenuActions::BackToMenu()
{
	menuContext->inLevels = false;
	if (!menuContext->inMenu)
	{
		menuContext->inMenu = true;
		menuContext->pathToFile = "file:///Resources/menuHTML/menu.html";
		ReloadPage();
		menuContext->currentLevel = 1;
	}
}

void MenuActions::ShowLevels()
{
	menuContext->currentLevelPage = 1;
	menuContext->currentLevelIndex = 1;
	menuContext->inLevels = true;
	menuContext->inMenu = false;
	menuContext->pathToFile = "file:///Resources/menuHTML/levels.html";
	ReloadPage();
	std::vector<std::string> levelCollection = this->levelManager->getAllLevels();
	for (std::vector<std::string>::iterator it = levelCollection.begin(); it != levelCollection.end(); ++it) {
		addLevelToMenu(menuContext->webView, menuContext->web_core, (*it).c_str());
	}
}

void MenuActions::addLevelToMenu(WebView* webView, WebCore* web_core, const char* naam)
{
	JSValue window = webView->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));

	if (window.IsObject())
	{
		JSArray args;
		WebString string = WebString::CreateFromUTF8(naam, strlen(naam) + 1);
		JSValue val = JSValue(string);
		args.Push(val);
		window.ToObject().Invoke(WSLit("insertRow"), args);
	}

	Sleep(50);
	web_core->Update();
}

void MenuActions::CallLevelEditMenuFunction(WebView* webView, WebCore* web_core, std::string action)
{
	JSValue window = webView->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));

	if (window.IsObject())
	{
		JSArray args;
		if (action == "switchToUp" || action == "switchToDown") {
			int level = menuContext->currentLevelIndex - ((menuContext->currentLevelPage - 1) * 8);
			JSValue val = JSValue(level);
			args.Push(val);
		}
		if (action == "switchToUp" && menuContext->currentLevelIndex == ((menuContext->currentLevelPage - 1) * 8) + 1) {
			//bijvoorbeeld nummer 9 naar 8 
			window.ToObject().Invoke(WSLit("switchToUpAndPage"), args);
		}
		else if (action == "switchToDown" && menuContext->currentLevelIndex == menuContext->currentLevelPage * 8) {
			//bijvoorbeeld nummer 8 naar 9 
			window.ToObject().Invoke(WSLit("switchToUpAndPageDown"), args);
		}
		else
			window.ToObject().Invoke(WSLit(action.c_str()), args);
	}

	Sleep(50);
	web_core->Update();

}

void MenuActions::ReloadPage()
{
	WebURL url(WSLit(menuContext->pathToFile));
	menuContext->webView->LoadURL(url);
	menuContext->webView->SetTransparent(true);

	while (menuContext->webView->IsLoading())
	{
		menuContext->web_core->Update();
	}

	Sleep(100);
	menuContext->web_core->Update();
}

void MenuActions::ShowIntruction()
{
	menuContext->inMenu = false;
	menuContext->pathToFile = "file:///Resources/menuHTML/instruction.html";
	ReloadPage();
}

void MenuActions::ShowHighscore()
{
	menuContext->inMenu = false;
	menuContext->pathToFile = "file:///Resources/menuHTML/score.html";
	ReloadPage();
	
	if(scoreManager->GetScores().size() < 1) return;
	
	std::map<std::string, int>::iterator it;
	for (it = scoreManager->GetScores().begin(); it != scoreManager->GetScores().end(); ++it) {
		addHighScoreToMenu(menuContext->webView, menuContext->web_core, it->first.c_str(),it->second);
	}
}

void MenuActions::NavigateUp()
{
	if (menuContext->inLevels)
	{
		int minLevel = ((menuContext->currentLevelPage - 1) * 8) + 1;
		if (menuContext->currentLevelIndex > minLevel)
		{
			menuContext->currentLevelIndex--;
			CallLevelEditMenuFunction(menuContext->webView, menuContext->web_core, std::string("selectionUp"));
		}
	}
	else if (menuContext->currentLevel > 1 && menuContext->inMenu)
	{
		menuContext->currentLevel -= 1;
		std::cout << menuContext->currentLevel;
		callDirectJSFunction(menuContext->webView, menuContext->web_core, menuContext->currentLevel);
	}
}

void MenuActions::NavigateDown()
{
	if (menuContext->inLevels)
	{
		int maxLevel;
		if (menuContext->currentLevelPage * 8 < this->levelManager->getAllLevels().size())
			maxLevel = menuContext->currentLevelPage * 8;
		else
			maxLevel = this->levelManager->getAllLevels().size();

		if (menuContext->currentLevelIndex < maxLevel)
		{
			menuContext->currentLevelIndex++;
			CallLevelEditMenuFunction(menuContext->webView, menuContext->web_core, std::string("selectionDown"));
		}
	}
	else if (menuContext->currentLevel < menuItems.size() && menuContext->inMenu)
	{
		menuContext->currentLevel += 1;
		callDirectJSFunction(menuContext->webView, menuContext->web_core, menuContext->currentLevel);
	}
}

void MenuActions::NavigateLeft()
{
	if (menuContext->inLevels) {
		CallLevelEditMenuFunction(menuContext->webView, menuContext->web_core, std::string("prevPage"));
		menuContext->currentLevelPage--;
		menuContext->currentLevelIndex = (menuContext->currentLevelPage - 1) * 8 + 1;
	}
}

void MenuActions::NavigateRight()
{
	if (menuContext->inLevels) {
		CallLevelEditMenuFunction(menuContext->webView, menuContext->web_core, std::string("nextPage"));
		menuContext->currentLevelIndex = (menuContext->currentLevelPage * 8) + 1;
		menuContext->currentLevelPage++;
	}
}

void MenuActions::NavigateComfirm()
{
	if (menuContext->inMenu)
	{
		std::map <int, void(MenuActions::*)()>::iterator it;
		for (it = menuItems.begin(); it != menuItems.end(); ++it)
		{
			if (it->first == menuContext->currentLevel)
			{
				auto function = it->second;
				(this->*function)();
				break;
			}
		}
	}
}

void MenuActions::SwitchToUp()
{
	if (menuContext->inLevels && menuContext->currentLevelIndex > 1) {
		CallLevelEditMenuFunction(menuContext->webView, menuContext->web_core, std::string("switchToUp"));
		this->levelManager->swapSequence(menuContext->currentLevelIndex, menuContext->currentLevelIndex - 1);
		if (menuContext->currentLevelIndex == ((menuContext->currentLevelPage - 1) * 8) + 1) {
			menuContext->currentLevelPage--;
			menuContext->currentLevelIndex = menuContext->currentLevelPage * 8;
		}
		else
			menuContext->currentLevelIndex--;
	}
}

void MenuActions::SwitchToDown()
{
	int maxLevel = this->levelManager->getAllLevels().size();
	if (menuContext->inLevels && menuContext->currentLevelIndex < maxLevel) {
		CallLevelEditMenuFunction(menuContext->webView, menuContext->web_core, std::string("switchToDown"));
		this->levelManager->swapSequence(menuContext->currentLevelIndex, menuContext->currentLevelIndex + 1);
		if (menuContext->currentLevelIndex == menuContext->currentLevelPage * 8)
		{
			menuContext->currentLevelPage++;
			menuContext->currentLevelIndex = ((menuContext->currentLevelPage - 1) * 8) + 1;
		}
		else
			menuContext->currentLevelIndex++;
	}
}

void MenuActions::addHighScoreToMenu(Awesomium::WebView* webView, Awesomium::WebCore* web_core, const char* naam, int score)
{
	JSValue window = webView->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));

	if (window.IsObject())
	{
		JSArray args;
		JSValue key = JSValue(naam);
		JSValue val = JSValue(score);
		args.Push(key);
		args.Push(val);
		window.ToObject().Invoke(WSLit("addScore"), args);
	}

	Sleep(50);
	web_core->Update();
}

void MenuActions::callDirectJSFunction(WebView* webView, WebCore* web_core, int currentLevel)
{
	JSValue window = webView->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));

	if (window.IsObject())
	{
		JSArray args;
		JSValue val = JSValue(currentLevel);
		args.Push(val);
		window.ToObject().Invoke(WSLit("myfunc"), args);
	}

	Sleep(50);
	web_core->Update();
}