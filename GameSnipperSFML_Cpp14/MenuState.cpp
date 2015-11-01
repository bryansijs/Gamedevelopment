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

void MenuState::Terminate()
{
	delete this;
}

void MenuState::ShowIntruction()
{
	inMenu = false;
	pathToFile = "file:///Resources/menuHTML/instruction.html";
	ReloadPage();
}

void MenuState::RunGame()
{
	BaseState* gameState = new GameState(this->context, this->stateManager);
	stateManager->AddState(gameState);
	stateManager->StartNextState();
}

void MenuState::ShowAbout()
{
	inMenu = false;
	pathToFile = "file:///Resources/menuHTML/about.html";
	ReloadPage();
}

void MenuState::BackToMenu()
{
	inMenu = true;
	pathToFile = "file:///Resources/menuHTML/menu.html";
	ReloadPage();
	currentLevel = 1;
}

void MenuState::ReloadPage()
{
	WebURL url(WSLit(pathToFile));
	webView->LoadURL(url);
	webView->SetTransparent(true);

	while (webView->IsLoading())
		web_core->Update();

	Sleep(300);
	web_core->Update();
}

void MenuState::Run()
{
	inMenu = true;
	running = true;
	std::map <int, void(MenuState::*)()> my_map;
	my_map[1] = &MenuState::RunGame;
	my_map[2] = &MenuState::ShowIntruction;
	my_map[3] = &MenuState::ShowAbout;

	currentLevel = 1;
	sf::Event event;

	// Awesomium init
	MethodDispatcher dispatcher;
	web_core = WebCore::Initialize(WebConfig());
	webView = web_core->CreateWebView(960, 640);

	// Load Page
	pathToFile = "file:///Resources/menuHTML/menu.html";
	ReloadPage();

	//Create Bitmap
	BitmapSurface* surface = static_cast<Awesomium::BitmapSurface*>(webView->surface());
	sf::Texture uiTexture;
	uiTexture.create(960, 640);
	sf::Uint8* pixels = new sf::Uint8[960 * 640 * 4];

	sf::SoundBuffer sfx;
	sfx.loadFromFile("./Resources/Music/title.ogg");
	sf::Sound music(sfx);
	music.setVolume(50.0f);
	music.setLoop(true);
	music.play();


	while (running && context->window.isOpen()) {

		context->window.clear();

		while (context->window.pollEvent(event)) {
			
			
			if (event.type == sf::Event::Closed)
			{
				context->window.close();
				//running = false;
			}
			
			switch(event.type)
			{
			case sf::Event::KeyPressed: {

				Input::EventOccured(event);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					if (currentLevel > 1)
					{
						currentLevel = currentLevel - 1;
				
						callDirectJSFunction(webView, web_core, currentLevel);
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					if (currentLevel < 3)
					{
						currentLevel = currentLevel + 1;
						callDirectJSFunction(webView, web_core, currentLevel);
					}
				}
				if (event.key.code == sf::Keyboard::Escape) {
					if(!inMenu)
					{
						BackToMenu();
					}
				}
				if (event.key.code == sf::Keyboard::Return) {
					std::map <int, void(MenuState::*)()>::iterator it;
					for (it = my_map.begin(); it != my_map.end(); ++it)
					{
						if (it->first == currentLevel)
						{
							music.stop();
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