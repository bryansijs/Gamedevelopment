#include "stdafx.h"
#include "MenuActions.h"
#include "StateManager.h"
#include "GameState.h"
#include "MenuContext.h"
#include <Awesomium/STLHelpers.h>
#include "Context.h"

using namespace Awesomium;

MenuActions::MenuActions(StateManager* stateManager, MenuContext* menuContext)
{
	MenuActions::stateManager = stateManager;
	MenuActions::menuContext = menuContext;
}

void MenuActions::ExitGame()
{
	menuContext->context->window.close();
	stateManager->PopState();
}

void MenuActions::RunGame()
{
	menuContext->music->stop();
	GameState* gameState = new GameState(menuContext->context, stateManager);
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
	if (!menuContext->inMenu)
	{
		menuContext->inMenu = true;
		menuContext->pathToFile = "file:///Resources/menuHTML/menu.html";
		ReloadPage();
		menuContext->currentLevel = 1;
	}
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

void MenuActions::NavigateUp()
{
	if (menuContext->currentLevel > 1)
	{
		menuContext->currentLevel--;
		callDirectJSFunction(menuContext->webView, menuContext->web_core, menuContext->currentLevel);
	}
}

void MenuActions::NavigateDown()
{
	if (menuContext->currentLevel < 4)
	{
		menuContext->currentLevel++;
		callDirectJSFunction(menuContext->webView, menuContext->web_core, menuContext->currentLevel);
	}
}

void MenuActions::NavigateComfirm()
{
	switch(menuContext->currentLevel)
	{
		case 1:
			RunGame();
			return;
		case 2:
			ShowIntruction();
			return;
		case 3:
			ShowAbout();
			return;
		case 4:
			ExitGame();
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