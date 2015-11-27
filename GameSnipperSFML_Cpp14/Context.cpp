#include "stdafx.h"
#include "Context.h"
#include <Awesomium/WebCore.h>

#include "KeyMapping.h"

Context::Context(int screenWidth, int screenHeight)
{
	screenDimensions = { new sf::Vector2i(screenWidth, screenHeight)};
	window.create(sf::VideoMode(screenDimensions->x, screenDimensions->y), "ECHO GAME!!!!");
	window.setKeyRepeatEnabled(false);
	window.setMouseCursorVisible(false);
	this->web_core = Awesomium::WebCore::Initialize(Awesomium::WebConfig());
}

Context::~Context()
{
	
}