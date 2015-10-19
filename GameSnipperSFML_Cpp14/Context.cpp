#include "stdafx.h"
#include "Context.h"
#include "Unit.h"
#include "MoveBehaviour.h"
#include "DrawBehaviour.h"
#include "Player.h"

Context::Context(int screenHeight, int screenWidth)
{
	screenDimensions = { new sf::Vector2i(screenHeight, screenWidth)};
	window.create(sf::VideoMode(screenDimensions->x, screenDimensions->y), "ECHO GAME!!!!");
	window.setKeyRepeatEnabled(false);

	Unit* p{ new Player(&this->allMoveBehaviours, &this->allDrawBehaviours, &this->allUnits)};
	

}


Context::~Context()
{
}

