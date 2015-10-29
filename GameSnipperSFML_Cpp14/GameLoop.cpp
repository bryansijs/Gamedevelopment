#include <SFML\Graphics.hpp>
#include "stdafx.h"
#include "GameLoop.h"
#include "Context.h"
#include "Unit.h"
#include "DrawBehaviour.h"
#include "NormalDrawBehaviour.h"
#include "MoveBehaviour.h"
#include "LevelImporter.h"
#include "PlayerActions.h"
#include "Time.h"

LevelImporter* l;
Level* lev;
GameLoop::GameLoop(Context* c)
{
	this->context = c;
	l = new LevelImporter(context->drawContainer);

	l->Import("./Resources/levels/Level_New.json");
	l->Prepare();
}

GameLoop::~GameLoop()
{
}

void GameLoop::run()
{
	Level* lev = l->getLevel();
	l->Clear();
	lev->Start(context->player, &context->window.getSize());

	sf::FloatRect rect(lev->getViewPortX(), lev->getViewPortY(), context->window.getSize().x, context->window.getSize().y);
	sf::View view;
	view.reset(rect);

	context->window.setView(view);

	sf::Clock deltaClock;
	sf::Event event;

	while (context->window.isOpen()) {
		Time::deltaTime = (float)deltaClock.restart().asMilliseconds() / 10;
		Time::runningTime += Time::deltaTime;

		sf::Vector2f s = context->player->position;
		sf::Vector2i worldPos = context->window.mapCoordsToPixel(s);

		lev->draw(&context->window, &view);
		lev->update();

		if (lev->getDoEvents()) {
			while (context->window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					context->window.close();
					break;
				}

				if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
				{
					Input::EventOccured(event);
					context->playerInput.CatchInput();
				}
			}

			context->playerActions.ProcessActions(context->playerInput.GetActiveKeys());
			lev->updateViewPort(worldPos);
		}

		context->moveContainer->Update();
		context->drawContainer->Draw(&context->window);

		context->window.setView(view);
		context->window.display();
		context->window.clear();

	}
}