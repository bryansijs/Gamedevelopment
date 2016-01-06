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
#include "KeyMapping.h"
#include <fstream>

using namespace Awesomium;




WinState::WinState(Context* context, StateManager* stateManager, LevelManager* levelManager, ScoreManager* scoreManager)
{
	winContext = new WinContext(context);
	this->stateManager = stateManager;
	this->levelManager = levelManager;
	this->scoreManager = scoreManager;

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
	setScore(50);
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
		if (Input::GetKeyDown(KeyMapping::GetKey("escape"))) {
			ToMenu();
		}

		if (winContext->event.type == sf::Event::TextEntered)
		{
			if (winContext->event.text.unicode < 128) {
				addNameCharacter(new char(static_cast<char>(winContext->event.text.unicode)));
				winContext->scoreName.append(new char(static_cast<char>(winContext->event.text.unicode)));
				winContext->amountNameChars++;
			}
			if(winContext->amountNameChars > 2)
			{
				//TODO: Safe 
				ToMenu();
			}
		}
		
		/*if (winContext->event.type == sf::Event::KeyPressed)
		{
			Input::EventOccured(winContext->event);

			if (Input::GetKeyDown("Return")) {
				if(!winContext->saved)
				{
					SetHighscore();
				}
			}
			else
			{
				ToMenu();
			}
		}*/
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
	MenuState* menuState = new MenuState(winContext->context, stateManager, levelManager,scoreManager);

	stateManager->AddState(menuState);
	stateManager->StartNextState();
}

WinState::~WinState()
{
	delete winContext;
}


void WinState::SetHighscore()
{
	std::cout << "excape";
}

void WinState::addNameCharacter(const char* character)
{
	JSValue window = winContext->webView->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));

	if (window.IsObject())
	{
		JSArray args;
		WebString string = WebString::CreateFromUTF8(character, 1);
		JSValue val = JSValue(string);
		args.Push(val);
		window.ToObject().Invoke(WSLit("insertChar"), args);
	}

	Sleep(50);
	winContext->web_core->Update();
}

void WinState::setScore(int score)
{
	JSValue window = winContext->webView->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));

	if (window.IsObject())
	{
		JSArray args;
		JSValue val = JSValue(score);
		args.Push(val);
		window.ToObject().Invoke(WSLit("insertScore"), args);
	}

	Sleep(50);
	winContext->web_core->Update();
}
void WinState::addScore(std::string name, int score)
{
	std::ofstream highScorefile("./Resources/save/highscore.txt");
	if (highScorefile.is_open())
	{
		//highScorefile.clear();
		highScorefile << name << " " << score;
		highScorefile.close();
	}
	else
		std::cerr << "could not open highScore file";
}