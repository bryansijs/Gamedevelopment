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
#include "Input.h"
#include "GameState.h"
#include "StateManager.h"


using namespace Awesomium;

void callDirectJSFunction(WebView* webView, WebCore* web_core , int currentLevel)
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

void MenuState::Terminate()
{
	delete this;
}

void MenuState::Run()
{
	std::map <string, string> my_map;
	my_map["1"] = "newGame";
	my_map["2"] = "loadGame"; //TODO binnen Menu
	my_map["3"] = "level editor";
	my_map["4"] = "instruction";// in Menu
	my_map["5"] = "about";// in Menu

	std::cout << my_map.at("1") << std::endl;

	int currentLevel = 1;
	sf::Event event;

	// Awesomium init
	MethodDispatcher dispatcher;
	WebCore* web_core = WebCore::Initialize(WebConfig());
	int i = 0;
	WebView* webView = web_core->CreateWebView(960, 640);

	// Load Page
	WebURL url(WSLit("file:///Resources/menuHTML/menu.html"));
	webView->LoadURL(url);
	webView->SetTransparent(true);

	while (webView->IsLoading())
		web_core->Update();

	Sleep(300);
	web_core->Update();

	//Create Bitmap
	BitmapSurface* surface = static_cast<Awesomium::BitmapSurface*>(webView->surface());
	sf::Texture uiTexture;
	uiTexture.create(960, 640);
	sf:: Uint8* pixels = new sf::Uint8[960 * 640 * 4];

	while (context->window.isOpen()) {
		context->window.clear();

		while (context->window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				context->window.close();
		}

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			Input::EventOccured(event);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				if(currentLevel > 1)
				{
					currentLevel = currentLevel - 1;
					std::cout << currentLevel << std::endl;
					callDirectJSFunction(webView, web_core, currentLevel);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				if (currentLevel < 5)
				{
					currentLevel = currentLevel + 1;
					std::cout << currentLevel << std::endl;
					callDirectJSFunction(webView, web_core, currentLevel);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				BaseState* gameState = new GameState(this->context, this->stateManager);
				stateManager->AddState(gameState);
				stateManager->StartNextState();
			}
		}

		// Create image from Bitmap
		surface = static_cast<Awesomium::BitmapSurface*>(webView->surface());
		const unsigned char* tempBuffer = surface->buffer();
		for (register int i = 0; i < 960 * 640 * 4; i += 4) {
			pixels[i] = tempBuffer[i + 2]; // B
			pixels[i + 1] = tempBuffer[i + 1]; // G
			pixels[i + 2] = tempBuffer[i]; // R
			pixels[i + 3] = tempBuffer[i + 3]; // Alpha
		}

		sf::Sprite ui(uiTexture);
		uiTexture.update(pixels);

		context->window.draw(ui);
		context->window.display();
	}
	
}

MenuState::MenuState(Context* c, StateManager* manager)
{
	this->context = c;
	this->stateManager = manager;
}


MenuState::~MenuState()
{
	//delete context;
}