#include <SFML\Graphics.hpp>
#include "stdafx.h"
#include "GameLoop.h"
#include "Context.h"
#include "Unit.h"
#include "DrawBehaviour.h"
#include "NormalDrawBehaviour.h"
#include "MoveBehaviour.h"


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
			context->allUnits.at(0)->moveBehaviour->Move(0.0f, 5.0f, 0.0f, 0.0f, 0.017f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			context->allUnits.at(0)->moveBehaviour->Move(5.0f, 0.0f, 0.0f, 0.0f, 0.017f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			context->allUnits.at(0)->moveBehaviour->Move(0.0f, 0.0f, 5.0f, 0.0f, 0.017f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			context->allUnits.at(0)->moveBehaviour->Move(0.0f, 0.0f, 0.0f, 5.0f, 0.017f);
		}

		for (int i = 0; i < context->getUnits().size(); i++) {
			Unit* u = context->getUnits().at(i);
			context->window.draw(u->drawBehaviour->getCurrentImage());
			
		}
		context->window.display();
		context->window.clear();

	}
}
