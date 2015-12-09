#include "stdafx.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>

#include "Context.h"
#include "WinContext.h"

#include "Input.h"
#include "WinState.h"
#include "MenuState.h"
#include "StateManager.h"

using namespace Awesomium;

WinState::WinState(Context* context, StateManager* stateManager, LevelManager* levelManager)
{
	winContext = new WinContext(context);
	this->stateManager = stateManager;
	this->levelManager = levelManager;

	sf::View view = winContext->context->window.getView();
	view.setCenter(480, 320);
	winContext->context->window.setView(view);

	// Awesomium init
	winContext->web_core = context->web_core;
	winContext->webView = winContext->web_core->CreateWebView(960, 640);

	// Load Page
	winContext->pathToFile = "file:///Resources/menuHTML/win.html";
	ReloadPage();

	//Create Bitmap
	winContext->surface = static_cast<Awesomium::BitmapSurface*>(winContext->webView->surface());

	winContext->texture.create(960, 640);
	winContext->pixels = new sf::Uint8[winContext->context->window.getSize().x * winContext->context->window.getSize().y * 4];

	winContext->sfx.loadFromFile("./Resources/sfx/victory.ogg");
	winContext->music = new sf::Sound(winContext->sfx);
	winContext->music->setVolume(50.0f);
	winContext->music->play();
}

void WinState::ReloadPage()
{
	WebURL url(WSLit(winContext->pathToFile));
	winContext->webView->LoadURL(url);
	winContext->webView->SetTransparent(true);

	while (winContext->webView->IsLoading())
	{
		winContext->web_core->Update();
	}

	Sleep(100);
	winContext->web_core->Update();
}

void WinState::Update()
{
	winContext->context->window.clear();

	while (winContext->context->window.pollEvent(winContext->event)) {
		if (winContext->event.type == sf::Event::KeyPressed)
		{
			Input::EventOccured(winContext->event);

			ToMenu();
		}
	}

	//Create image from Bitmap
	winContext->surface = static_cast<Awesomium::BitmapSurface*>(winContext->webView->surface());
	const unsigned char* tempBuffer = winContext->surface->buffer();

	for (register int i = 0; i < 960 * 640 * 4; i += 4) {
		winContext->pixels[i] = tempBuffer[i + 2]; // B
		winContext->pixels[i + 1] = tempBuffer[i + 1]; // G
		winContext->pixels[i + 2] = tempBuffer[i]; // R
		winContext->pixels[i + 3] = tempBuffer[i + 3]; // Alpha
	}

	sf::Sprite ui(winContext->texture);
	winContext->texture.update(winContext->pixels);

	winContext->context->window.draw(ui);
	winContext->context->window.display();
}

void WinState::ToMenu()
{
	winContext->music->stop();
	MenuState* menuState = new MenuState(winContext->context, stateManager, levelManager);

	stateManager->AddState(menuState);
	stateManager->StartNextState();
}

WinState::~WinState()
{
	delete winContext;
}
