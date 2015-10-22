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

	sf::Clock deltaClock;

	while (context->window.isOpen()) {
		context->window.clear();

		sf::Time deltaTime = deltaClock.restart();

		sf::Vector2f s = context->allUnits.at(0)->positions;
		sf::Vector2i worldPos = context->window.mapCoordsToPixel(s);

		sf::Event event;
		lev->draw(&context->window, &view);
		lev->update();

		if (lev->getDoEvents()) {
			while (context->window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					context->window.close();
					break;
				}
			}

			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
			{
				Input::EventOccured(event);

				context->playerInput.CatchInput();
				context->playerMovement.SetActiveKeys(context->playerInput.GetActiveKeys());
				context->playerMovement.Move(deltaTime.asMicroseconds());
			}

			lev->updateViewPort(worldPos);
		}

		context->window.draw(context->player->drawBehaviour->getCurrentImage());
		
		for (int i = 0; i < context->allDrawBehaviours.size(); i++) {
			context->window.draw(context->allDrawBehaviours.at(i)->getCurrentImage());
		}

		context->window.setView(view);
		context->window.display();
		context->window.clear();

	}
}