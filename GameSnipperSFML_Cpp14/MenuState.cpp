#include "stdafx.h"
#include "Context.h"
#include "MenuState.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>
#include "method_dispatcher.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>

#include "Context.h"
#include "MenuContext.h"

#include "Input.h"
#include "GameState.h"
#include "StateManager.h"

using namespace Awesomium;

void MenuState::Create(Context* context)
{
	menuContext = new MenuContext(context);
}

void MenuState::Terminate()
{
	delete menuContext;
	delete this;
}

void callDirectJSFunction(WebView* webView, WebCore* web_core, int currentLevel)
{
	JSValue window = webView->ExecuteJavascriptWithResult(
		WSLit("window"), WSLit(""));

	if (window.IsObject())
	{
		JSArray args;
		JSValue val = JSValue(currentLevel);
		args.Push(val);
		window.ToObject().Invoke(WSLit("myfunc"), args);
	}

	Sleep(300);
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
	BaseState* gameState = new GameState(menuContext->context, stateManager);
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
		menuContext->web_core->Update();

	Sleep(300);
	menuContext->web_core->Update();
}

void MenuState::Run()
{
	menuContext->inMenu = true;
	running = true;
	std::map <int, void(MenuState::*)()> my_map;
	my_map[1] = &MenuState::RunGame;
	my_map[2] = &MenuState::ShowIntruction;
	my_map[3] = &MenuState::ShowAbout;

	menuContext->currentLevel = 1;
	sf::Event event;

	// Awesomium init
	MethodDispatcher dispatcher;
	menuContext->web_core = WebCore::Initialize(WebConfig());
	menuContext->webView = menuContext->web_core->CreateWebView(960, 640);

	// Load Page
	menuContext->pathToFile = "file:///Resources/menuHTML/menu.html";
	ReloadPage();

	//Create Bitmap
	BitmapSurface* surface = static_cast<Awesomium::BitmapSurface*>(menuContext->webView->surface());
	sf::Texture uiTexture;
	uiTexture.create(960, 640);
	sf::Uint8* pixels = new sf::Uint8[960 * 640 * 4];

	sf::SoundBuffer sfx;
	sfx.loadFromFile("./Resources/Music/title.ogg");
	menuContext->music = new sf::Sound(sfx);
	menuContext->music->setVolume(50.0f);
	menuContext->music->setLoop(true);
	menuContext->music->play();


	while (running && menuContext->context->window.isOpen()) {

		menuContext->context->window.clear();

		while (menuContext->context->window.pollEvent(event)) {
			
			
			if (event.type == sf::Event::Closed)
			{
				menuContext->context->window.close();
				//running = false;
			}
			
			switch(event.type)
			{
			case sf::Event::KeyPressed: {

				Input::EventOccured(event);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					if (menuContext->currentLevel > 1)
					{
						menuContext->currentLevel = menuContext->currentLevel - 1;
				
						callDirectJSFunction(menuContext->webView, menuContext->web_core, menuContext->currentLevel);
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					if (menuContext->currentLevel < 3)
					{
						menuContext->currentLevel = menuContext->currentLevel + 1;
						callDirectJSFunction(menuContext->webView, menuContext->web_core, menuContext->currentLevel);
					}
				}
				if (event.key.code == sf::Keyboard::Escape) {
					if(!menuContext->inMenu)
					{
						BackToMenu();
					}
				}
				if (event.key.code == sf::Keyboard::Return) {
					std::map <int, void(MenuState::*)()>::iterator it;
					for (it = my_map.begin(); it != my_map.end(); ++it)
					{
						if (it->first == menuContext->currentLevel)
						{
							auto function = it->second;
							(this->*function)();
						}
					}
				}
			}; break;
			default: break;
			}
			
		}
		
		//Create image from Bitmap
		surface = static_cast<Awesomium::BitmapSurface*>(menuContext->webView->surface());
		const unsigned char* tempBuffer = surface->buffer();
		for (register int i = 0; i < 960 * 640 * 4; i += 4) {
			pixels[i] = tempBuffer[i + 2]; // B
			pixels[i + 1] = tempBuffer[i + 1]; // G
			pixels[i + 2] = tempBuffer[i]; // R
			pixels[i + 3] = tempBuffer[i + 3]; // Alpha
		}

		sf::Sprite ui(uiTexture);
		uiTexture.update(pixels);

		menuContext->context->window.draw(ui);
		menuContext->context->window.display();
	}

}

MenuState::MenuState(Context* c, StateManager* manager)
{
	menuContext->context = c;
	stateManager = manager;
}


MenuState::~MenuState()
{
	//delete context;
}