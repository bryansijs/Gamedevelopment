#include <SFML\Graphics.hpp>
#include "stdafx.h"
#include "GameLoop.h"
#include "Context.h"
#include "Unit.h"
#include "DrawBehaviour.h"
#include "NormalDrawBehaviour.h"
#include "MoveBehaviour.h"
#include "LevelImporter.h"

LevelImporter* l;
Level* lev;
GameLoop::GameLoop(Context* c)
{
	this->context = c;
	l = new LevelImporter(this->context->allDrawBehaviours);

	l->Import("./Resources/levels/Level_New.json");
	l->Prepare();
	this->context->allDrawBehaviours.swap(l->draws);
}

GameLoop::~GameLoop()
{
}

void GameLoop::run()
{
	Level* lev = l->getLevel();
	l->Clear();
	lev->Start(context->allUnits.at(0), &context->window.getSize());

	sf::FloatRect rect(lev->getViewPortX(), lev->getViewPortY(), context->window.getSize().x, context->window.getSize().y);
	sf::View view;
	view.reset(rect);

	context->window.setView(view);

	while (context->window.isOpen()) {
		context->window.clear();

		sf::Vector2f s = context->allUnits.at(0)->positions;
		sf::Vector2i worldPos = context->window.mapCoordsToPixel(s);


		sf::Event Event;
		lev->draw(&context->window, &view);
		lev->update();

		if (lev->getDoEvents()) {
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

			for (int i = 0; i < context->allDrawBehaviours.size(); i++) {
				context->window.draw(context->allDrawBehaviours.at(i)->getCurrentImage());
			}

			lev->updateViewPort(worldPos);
		}

		context->window.setView(view);
		context->window.display();
		context->window.clear();

	}
}
