#include "stdafx.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Context.h"
#include "LoseContext.h"

#include "Input.h"
#include "LoseState.h"
#include "MenuState.h"
#include "StateManager.h"

using namespace Awesomium;

LoseState::LoseState(Context* context, StateManager* stateManager, LevelManager* levelManager)
{
	loseContext = new LoseContext(context);
	this->stateManager = stateManager;
	this->levelManager = levelManager;

	sf::View view = loseContext->context->window.getView();
	view.setCenter(480, 320);
	loseContext->context->window.setView(view);

	// Awesomium init
	loseContext->web_core = context->web_core;
	loseContext->webView = loseContext->web_core->CreateWebView(960, 640);

	// Load Page
	loseContext->pathToFile = "file:///Resources/menuHTML/lose.html";
	ReloadPage();

	//Create Bitmap
	loseContext->surface = static_cast<Awesomium::BitmapSurface*>(loseContext->webView->surface());

	loseContext->texture.create(960, 640);
	loseContext->pixels = new sf::Uint8[loseContext->context->window.getSize().x * loseContext->context->window.getSize().y * 4];

	loseContext->sfx.loadFromFile("./Resources/sfx/defeat.ogg");
	loseContext->music = new sf::Sound(loseContext->sfx);
	loseContext->music->setVolume(50.0f);
	loseContext->music->play();
}

void LoseState::ReloadPage()
{
	WebURL url(WSLit(loseContext->pathToFile));
	loseContext->webView->LoadURL(url);
	loseContext->webView->SetTransparent(true);

	while (loseContext->webView->IsLoading())
	{
		loseContext->web_core->Update();
	}

	Sleep(100);
	loseContext->web_core->Update();
}

void LoseState::Update()
{
	loseContext->context->window.clear();

	while (loseContext->context->window.pollEvent(loseContext->event)) {
		if (loseContext->event.type == sf::Event::KeyPressed)
		{
			Input::EventOccured(loseContext->event);

			ToMenu();
		}
	}

	//Create image from Bitmap
	loseContext->surface = static_cast<Awesomium::BitmapSurface*>(loseContext->webView->surface());
	const unsigned char* tempBuffer = loseContext->surface->buffer();

	for (register int i = 0; i < 960 * 640 * 4; i += 4) {
		loseContext->pixels[i] = tempBuffer[i + 2]; // B
		loseContext->pixels[i + 1] = tempBuffer[i + 1]; // G
		loseContext->pixels[i + 2] = tempBuffer[i]; // R
		loseContext->pixels[i + 3] = tempBuffer[i + 3]; // Alpha
	}

	sf::Sprite ui(loseContext->texture);
	loseContext->texture.update(loseContext->pixels);

	loseContext->context->window.draw(ui);
	loseContext->context->window.display();
}

void LoseState::ToMenu()
{
	loseContext->music->stop();
	MenuState* menuState = new MenuState(loseContext->context, stateManager, levelManager);

	stateManager->AddState(menuState);
	stateManager->StartNextState();
}

LoseState::~LoseState()
{
}
