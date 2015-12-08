#include "stdafx.h"
#include "Context.h"
#include "MenuState.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "MenuContext.h"

#include "StateManager.h"
#include <filesystem>
#include <thread>
#include "Input.h"

using namespace Awesomium;

MenuState::MenuState(Context* context, StateManager* stateManager, LevelManager* levelManager)
{
	menuContext = new MenuContext(context);
	this->stateManager = stateManager;
	this->levelManager = levelManager;
	menuActions = new MenuActions(stateManager, menuContext, levelManager);

	menuContext->inMenu = true;
	menuContext->currentLevel = 1;

	// Awesomium init
	context->web_core = WebCore::Initialize(WebConfig());
	menuContext->webView = context->web_core->CreateWebView(960, 640);

	// Load Page
	menuContext->pathToFile = "file:///Resources/menuHTML/menu.html";
	menuActions->ReloadPage();

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

void MenuState::Update()
{
	menuContext->context->window.clear();

	while (menuContext->context->window.pollEvent(menuContext->event)) {
		if (menuContext->event.type == sf::Event::Closed)
		{
			menuActions->ExitGame();
			return;
		}

		if (menuContext->event.type == sf::Event::KeyPressed)
		{
			Input::EventOccured(menuContext->event);
			menuActions->CatchSingleInput();
			menuActions->ProcessActions();
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