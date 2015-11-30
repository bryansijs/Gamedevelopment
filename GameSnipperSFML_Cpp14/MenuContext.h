#pragma once

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>

#include <SFML/Audio.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "MenuActions.h"

class Context;
class StateManager;

class MenuContext
{
public:
	MenuContext(Context* context);
	~MenuContext();

	Context* context;

	int currentLevel;
	bool inMenu = false;
	char const* pathToFile;

	StateManager* stateManager;

	Awesomium::WebView* webView;
	Awesomium::WebCore* web_core;
	Awesomium::BitmapSurface* surface;

	sf::Event event;
	sf::Sound* music;
	sf::SoundBuffer sfx;
	sf::Texture texture;
	sf::Uint8* pixels;
};

