#include "stdafx.h"
#include "Context.h"
#include "MenuState.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>

#include "Context.h"
#include "MenuContext.h"

#include "Input.h"
#include "GameState.h"
#include "StateManager.h"

//temp stuff ----------------------------------------------------------------------------------------
#include "WinState.h"
#include "LoseState.h"

using namespace Awesomium;

MenuState::MenuState(Context* context, StateManager* stateManager)
{
	menuContext = new MenuContext(context);
	this->stateManager = stateManager;

	menuContext->inMenu = true;
	menuContext->currentLevel = 1;

	// Awesomium init
	menuContext->web_core = context->web_core;
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

void MenuState::ShowIntruction()
{
	menuContext->inMenu = false;
	menuContext->pathToFile = "file:///Resources/menuHTML/instruction.html";
	ReloadPage();
}

void MenuState::RunGame()
{
	menuContext->music->stop();

	GameState* gameState = new GameState(menuContext->context, stateManager);
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
	menuContext->inMenu = true;
	menuContext->pathToFile = "file:///Resources/menuHTML/menu.html";
	ReloadPage();
	menuContext->currentLevel = 1;
}

void MenuState::ReloadPage()
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
				if (menuContext->currentLevel > 1)
				{
					menuContext->currentLevel -= 1;
					callDirectJSFunction(menuContext->webView, menuContext->web_core, menuContext->currentLevel);
				}
			}

			if (Input::GetKeyDown("Down")) {
				if (menuContext->currentLevel < menuItems.size())
				{
					menuContext->currentLevel += 1;
					callDirectJSFunction(menuContext->webView, menuContext->web_core, menuContext->currentLevel);
				}
			}

			if (Input::GetKeyDown("Esc")) {
				if (!menuContext->inMenu)
				{
					BackToMenu();
				}
				
			}

			// temp stuff -------------------------------------------------------------------------------------------
			if (Input::GetKeyDown("Y")) {
				menuContext->music->stop();

				//Dit is nodig om een afbeelding te maken van wat er op dit moment word getoont. Deze word dan in de win/lose screen gebruikt als achtergrond omdat het niet met transparantie wil lukken
				((BitmapSurface*)menuContext->webView->surface())->SaveToPNG(Awesomium::WebString::CreateFromUTF8("./Resources/menuHTML/images/hold.png", strlen("./Resources/menuHTML/images/hold.png")));

				WinState* winState = new WinState(menuContext->context, stateManager);
				stateManager->AddState(winState);
				stateManager->StartNextState();
			}

			if (Input::GetKeyDown("U")) {
				menuContext->music->stop();

				//Dit is nodig om een afbeelding te maken van wat er op dit moment word getoont. Deze word dan in de win/lose screen gebruikt als achtergrond omdat het niet met transparantie wil lukken
				((BitmapSurface*)menuContext->webView->surface())->SaveToPNG(Awesomium::WebString::CreateFromUTF8("./Resources/menuHTML/images/hold.png", strlen("./Resources/menuHTML/images/hold.png")));

				LoseState* loseState = new LoseState(menuContext->context, stateManager);
				stateManager->AddState(loseState);
				stateManager->StartNextState();
			}
			//-------------------------------------------------------------------------------------------------------

			if (Input::GetKeyDown("Return")) {
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