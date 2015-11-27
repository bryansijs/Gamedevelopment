#include "stdafx.h"
#include "Context.h"
#include "MenuState.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/WebString.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>

#include "MenuContext.h"

#include "Input.h"
#include "GameState.h"
#include "StateManager.h"
#include "JSConsole.h"

using namespace Awesomium;

MenuState::MenuState(Context* context, StateManager* stateManager, LevelManager* levelManager)
{
	menuContext = new MenuContext(context);
	this->stateManager = stateManager;
	this->levelManager = levelManager;

	menuContext->inMenu = true;
	menuContext->currentLevel = 1;

	// Awesomium init
	menuContext->web_core = WebCore::Initialize(WebConfig());
	menuContext->webView = menuContext->web_core->CreateWebView(960, 640);

	// Load Page
	menuContext->pathToFile = "file:///Resources/menuHTML/menu.html";
	ReloadPage();

	//Create Bitmap
	menuContext->surface = static_cast<Awesomium::BitmapSurface*>(menuContext->webView->surface());

	menuContext->texture.create(960, 640);
	menuContext->pixels = new sf::Uint8[menuContext->context->window.getSize().x * menuContext->context->window.getSize().y * 4];

	menuContext->sfx.loadFromFile("./Resources/Music/title.ogg");
	menuContext->music = new sf::Sound(menuContext->sfx);
	menuContext->music->setVolume(50.0f);
	menuContext->music->setLoop(true);
	menuContext->music->play();
}

MenuState::~MenuState()
{
	delete menuContext;
}

void MenuState::Terminate()
{
	terminate = true;
}

void MenuState::CallLevelEditMenuFunction(WebView* webView, WebCore* web_core, std::string action)
{
	JSValue window = webView->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));

	if (window.IsObject())
	{
		JSArray args;
		if (action == "switchToUp" || action == "switchToDown") {
			int level = menuContext->currentLevelIndex - ((menuContext->currentLevelPage-1) * 8);
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

void callDirectJSFunction(WebView* webView, WebCore* web_core, int currentLevel)
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

void addLevelToMenu(WebView* webView, WebCore* web_core, const char* naam)
{
	JSValue window = webView->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));

	if (window.IsObject())
	{
		JSArray args;
		WebString string = WebString::CreateFromUTF8(naam, strlen(naam) +1);
		JSValue val = JSValue(string);
		bool test = val.IsString();
		args.Push(val);
		window.ToObject().Invoke(WSLit("insertRow"), args);
	}

	Sleep(50);
	web_core->Update();
}

void MenuState::ShowIntruction()
{
	menuContext->inMenu = false;
	menuContext->pathToFile = "file:///Resources/menuHTML/instruction.html";
	ReloadPage();
}

void MenuState::ShowLevels()
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

void MenuState::RunGame()
{
	menuContext->inMenu = false;
	menuContext->music->stop();

	GameState* gameState = new GameState(menuContext->context, stateManager,this->levelManager);
	stateManager->AddState(gameState);
	stateManager->StartNextState();
}

void MenuState::ShowAbout()
{
	menuContext->inMenu = false;
	menuContext->pathToFile = "file:///Resources/menuHTML/about.html";
	ReloadPage();
}

void MenuState::BackToMenu()
{
	menuContext->inLevels = false;
	menuContext->inMenu = true;
	menuContext->pathToFile = "file:///Resources/menuHTML/menu.html";
	ReloadPage();
	menuContext->currentLevel = 1;
}

void MenuState::ReloadPage()
{
	JSConsole* listener = new JSConsole();
	WebURL url(WSLit(menuContext->pathToFile));
	menuContext->webView->LoadURL(url);
	menuContext->webView->SetTransparent(true);
	menuContext->webView->set_view_listener(listener);

	while (menuContext->webView->IsLoading())
	{
		menuContext->web_core->Update();
	}
		
	Sleep(100);
	menuContext->web_core->Update();
}

void MenuState::Update()
{
	menuContext->context->window.clear();

	while (menuContext->context->window.pollEvent(menuContext->event)) {
		if (menuContext->event.type == sf::Event::Closed)
		{
			menuContext->context->window.close();
			stateManager->PopState();
			return;
		}

		if (menuContext->event.type == sf::Event::KeyPressed)
		{
			Input::EventOccured(menuContext->event);

			if (Input::GetKeyDown("Up")) {
				if(menuContext->inLevels)
				{
					int minLevel = ((menuContext->currentLevelPage-1) * 8 ) + 1;
					if(menuContext->currentLevelIndex > minLevel)
					{
						menuContext->currentLevelIndex--;
						CallLevelEditMenuFunction(menuContext->webView, menuContext->web_core, std::string("selectionUp"));
					}					
				}
				else if (menuContext->currentLevel > 1 && menuContext->inMenu)
				{
					menuContext->currentLevel -= 1;
					callDirectJSFunction(menuContext->webView, menuContext->web_core, menuContext->currentLevel);
				}
			}

			if (Input::GetKeyDown("Down")) {
				if (menuContext->inLevels)
				{
					int maxLevel = 0;
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
			if (Input::GetKeyDown("Left")) {
				if (menuContext->inLevels) {
					CallLevelEditMenuFunction(menuContext->webView, menuContext->web_core, std::string("prevPage"));
					menuContext->currentLevelPage--;
					menuContext->currentLevelIndex = (menuContext->currentLevelPage-1) * 8 + 1;
				}
			}
			if (Input::GetKeyDown("Right")) {
				if (menuContext->inLevels) {
					CallLevelEditMenuFunction(menuContext->webView, menuContext->web_core, std::string("nextPage"));
					menuContext->currentLevelIndex = (menuContext->currentLevelPage * 8) + 1;
					menuContext->currentLevelPage++;
				}
			}
			if (Input::GetKeyDown("K")) {
				if (menuContext->inLevels && menuContext->currentLevelIndex > 1) {
					CallLevelEditMenuFunction(menuContext->webView, menuContext->web_core, std::string("switchToUp"));
					this->levelManager->swapSequence(menuContext->currentLevelIndex, menuContext->currentLevelIndex - 1);
					if (menuContext->currentLevelIndex == ((menuContext->currentLevelPage - 1) * 8) + 1){
						menuContext->currentLevelPage --;
						menuContext->currentLevelIndex = menuContext->currentLevelPage * 8;
					}
					else
						menuContext->currentLevelIndex--;
				}
			}
			if (Input::GetKeyDown("L")) {
					int maxLevel = this->levelManager->getAllLevels().size();
				if (menuContext->inLevels && menuContext->currentLevelIndex < maxLevel) {
					CallLevelEditMenuFunction(menuContext->webView, menuContext->web_core, std::string("switchToDown"));
					this->levelManager->swapSequence(menuContext->currentLevelIndex, menuContext->currentLevelIndex + 1);
					if(menuContext->currentLevelIndex == menuContext->currentLevelPage *8)
					{
						menuContext->currentLevelPage++;
						menuContext->currentLevelIndex = ((menuContext->currentLevelPage - 1) * 8) + 1;
					}
					else
						menuContext->currentLevelIndex++;
				}
			}

			if (Input::GetKeyDown("Esc")) {
				if (!menuContext->inMenu)
				{
					BackToMenu();
				}
			}

			if (Input::GetKeyDown("Return")) {

				if(menuContext->inMenu)
				{
					std::map <int, void(MenuState::*)()>::iterator it;
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
		}
	}
		
	//Create image from Bitmap
	menuContext->surface = static_cast<Awesomium::BitmapSurface*>(menuContext->webView->surface());
	const unsigned char* tempBuffer = menuContext->surface->buffer();

	for (register int i = 0; i < 960 * 640 * 4; i += 4) {
		menuContext->pixels[i] = tempBuffer[i + 2]; // B
		menuContext->pixels[i + 1] = tempBuffer[i + 1]; // G
		menuContext->pixels[i + 2] = tempBuffer[i]; // R
		menuContext->pixels[i + 3] = tempBuffer[i + 3]; // Alpha
	}

	sf::Sprite ui(menuContext->texture);
	menuContext->texture.update(menuContext->pixels);

	menuContext->context->window.draw(ui);
	menuContext->context->window.display();

	if (terminate)
	{
		delete this;
	}
}