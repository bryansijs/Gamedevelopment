#pragma once

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

class Context;

class MenuContext
{
public:
	MenuContext(Context* context);
	~MenuContext();

	Context* context;

	int currentLevel;
	char const* pathToFile;
	bool inMenu = false;

	Awesomium::WebView* webView;
	Awesomium::WebCore* web_core;

	StateManager* stateManager;
	sf::Sound* music;
};

