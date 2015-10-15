#include <SFML\Graphics.hpp>
#include "stdafx.h"
#include "GameLoop.h"
#include "Context.h"
#include "Unit.h"
#include "DrawBehaviour.h"
#include "NormalDrawBehaviour.h"


GameLoop::GameLoop(Context* c)
{
	this->context = c;
}

GameLoop::~GameLoop()
{
}

void GameLoop::run()
{
	while (context->window.isOpen()) {
		sf::Event Event;

		while (context->window.pollEvent(Event)) {
			switch (Event.type) {
			case sf::Event::Closed:
				context->window.close();
				break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			
		}

		for (int i = 0; i < context->getUnits().size(); i++) {
			Unit* u = context->getUnits().at(i);
			//u->drawBehaviour->
			
		}

	}
}
