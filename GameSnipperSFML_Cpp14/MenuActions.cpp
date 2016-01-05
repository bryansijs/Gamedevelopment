#include "stdafx.h"
#include "MenuActions.h"
#include "StateManager.h"
#include "GameState.h"
#include "MenuContext.h"
#include <Awesomium/STLHelpers.h>
#include "Context.h"
#include "KeyMapping.h"
#include "KeyMappingImporter.h"
#include "KeyMappingExporter.h"
#include <codecvt>

using namespace Awesomium;

MenuActions::MenuActions(StateManager* stateManager, MenuContext* menuContext, LevelManager* levelManager)
{
	MenuActions::stateManager = stateManager;
	MenuActions::menuContext = menuContext;
	MenuActions::levelManager = levelManager;
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

	if (editingKey)
	{
		EditKey();
	}
}

void MenuActions::EditKey()
{
	if (menuContext->event.type == sf::Event::KeyPressed)
	{
		Input::EventOccured(menuContext->event);

		if (menuContext->event.text.unicode < 128)
		{
			std::string key = Input::GetKey(menuContext->event.key.code);

			if (key != "Return")
			{
				if (key == "Escape")
				{
					editingKey = false;
					ShowControls();
					return;
				}

				if (!KeyMapping::KeyInUse(key) || KeyMapping::GetMap(key) == currentMap)
				{
					KeyMapping::ChangeKey(currentMap, key);
					std::string mappingString = KeyMappingExporter::MappingToString(KeyMapping::GetMapping());
					KeyMappingExporter::SaveToFile(mappingString);
					editingKey = false;
					ShowControls();
				}
				else
				{
					CallDirectJSFunction("invalidKey", "visible");
				}
			}
		}
	}
}

void MenuActions::ExitGame()
{
	menuContext->context->window.close();
	stateManager->PopState();
}

void MenuActions::RunGame()
{
	menuContext->music->stop();
	GameState* gameState = new GameState(menuContext->context, stateManager, levelManager);
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
	menuContext->inControls = false;
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
		addLevelToMenu(menuContext->webView, menuContext->context->web_core, (*it).c_str());
	}
}

void MenuActions::ShowControls()
{
	menuContext->currentLevel = 1;
	menuContext->inMenu = false;
	menuContext->inControls = true;
	menuContext->pathToFile = "file:///Resources/menuHTML/controls.html";
	ReloadPage();

	std::multimap<std::string, std::string> mapping = KeyMapping::GetMapping();
	
	std::map<int, std::string>::iterator vit;
	for (vit = editableMappings.begin(); vit != editableMappings.end(); ++vit)
	{
		multimap<std::string, std::string>::iterator it;
		for (it = mapping.begin(); it != mapping.end(); ++it)
		{
			if (it->first == vit->second)
			{
				std::string map = it->first + "," + it->second;
				CallDirectJSFunction("addMap", map.c_str());
			}
		}
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
		menuContext->context->web_core->Update();
	}

	Sleep(100);
	menuContext->context->web_core->Update();
}

void MenuActions::ShowIntruction()
{
	menuContext->inMenu = false;
	menuContext->pathToFile = "file:///Resources/menuHTML/instruction.html";
	ReloadPage();
}

void MenuActions::NavigateUp()
{
	if (menuContext->inLevels)
	{
		int minLevel = ((menuContext->currentLevelPage - 1) * 8) + 1;
		if (menuContext->currentLevelIndex > minLevel)
		{
			menuContext->currentLevelIndex--;
			CallLevelEditMenuFunction(menuContext->webView, menuContext->context->web_core, std::string("selectionUp"));
		}
	}
	else if (menuContext->currentLevel > 1 && menuContext->inControls && !editingKey)
	{
		menuContext->currentLevel -= 1;
		CallDirectJSFunction("setSelected", menuContext->currentLevel);
	}
	else if (menuContext->currentLevel > 1 && menuContext->inMenu)
	{
		menuContext->currentLevel -= 1;
		callDirectJSFunction(menuContext->webView, menuContext->context->web_core, menuContext->currentLevel);
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
			CallLevelEditMenuFunction(menuContext->webView, menuContext->context->web_core, std::string("selectionDown"));
		}
	}
	else if (menuContext->currentLevel < editableMappings.size() && menuContext->inControls && !editingKey)
	{
		menuContext->currentLevel += 1;
		CallDirectJSFunction("setSelected", menuContext->currentLevel);
	}
	else if (menuContext->currentLevel < menuItems.size() && menuContext->inMenu)
	{
		menuContext->currentLevel += 1;
		callDirectJSFunction(menuContext->webView, menuContext->context->web_core, menuContext->currentLevel);
	}
}

void MenuActions::NavigateLeft()
{
	if (menuContext->inLevels) {
		CallLevelEditMenuFunction(menuContext->webView, menuContext->context->web_core, std::string("prevPage"));
		menuContext->currentLevelPage--;
		menuContext->currentLevelIndex = (menuContext->currentLevelPage - 1) * 8 + 1;
	}
}

void MenuActions::NavigateRight()
{
	if (menuContext->inLevels) {
		CallLevelEditMenuFunction(menuContext->webView, menuContext->context->web_core, std::string("nextPage"));
		menuContext->currentLevelIndex = (menuContext->currentLevelPage * 8) + 1;
		menuContext->currentLevelPage++;
	}
}

void MenuActions::NavigateComfirm()
{
	if (menuContext->inControls && confirmed)
	{
		std::map<int, std::string>::iterator it;
		for (it = editableMappings.begin(); it != editableMappings.end(); ++it)
		{
			if (it->first == menuContext->currentLevel)
			{
				currentMap = it->second;
			}
		}

		CallDirectJSFunction("popup", "visible");
		editingKey = true;
	}

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

		confirmed = true;
	}
}

void MenuActions::SwitchToUp()
{
	if (menuContext->inLevels && menuContext->currentLevelIndex > 1) {
		CallLevelEditMenuFunction(menuContext->webView, menuContext->context->web_core, std::string("switchToUp"));
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
		CallLevelEditMenuFunction(menuContext->webView, menuContext->context->web_core, std::string("switchToDown"));
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

void MenuActions::CallDirectJSFunction(std::string function, std::string params)
{
	JSValue window = menuContext->webView->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));

	if (window.IsObject())
	{
		JSArray args;
		WebString string = WebString::CreateFromUTF8(params.c_str(), strlen(params.c_str()) + 1);
		JSValue val = JSValue(string);
		args.Push(val);
		window.ToObject().Invoke(WSLit(function.c_str()), args);
	}

	Sleep(50);
	menuContext->context->web_core->Update();
}

void MenuActions::CallDirectJSFunction(std::string function, int param)
{
	JSValue window = menuContext->webView->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));

	if (window.IsObject())
	{
		JSArray args;
		JSValue val = JSValue(param);
		args.Push(val);
		window.ToObject().Invoke(WSLit(function.c_str()), args);
	}

	Sleep(50);
	menuContext->context->web_core->Update();
}