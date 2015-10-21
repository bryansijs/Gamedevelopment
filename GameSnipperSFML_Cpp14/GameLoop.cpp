#include <SFML\Graphics.hpp>

#include <string>
#include <iostream>
#include <memory>

#include "stdafx.h"
#include "GameLoop.h"
#include "Context.h"
#include "Player.h"
#include "DrawBehaviour.h"
#include "NormalDrawBehaviour.h"
#include "MoveBehaviour.h"
#include "LevelImporter.h"
#include "Input.h"

bool doEvents = true;

bool moveDown = true;
int t_value = 0;
int t_max = 0;

bool moveRight = true;
int r_value = 0;
int r_max = 0;

void updateViewPort(sf::Vector2i &worldPos)
{
	//updateVP
	if (worldPos.y > 640)
	{
		doEvents = false;
		t_max += 320;
		moveDown = true;
	}

	if (worldPos.y < 0)
	{
		doEvents = false;
		t_max -= 320;
		moveDown = false;
	}

	if (worldPos.x > 960)
	{
		doEvents = false;
		r_max += 480;
		moveRight = true;
	}

	if (worldPos.x < 0)
	{
		doEvents = false;
		r_max -= 480;
		moveRight = false;
	}
}

void MoveView(sf::View &view)
{
	if (moveDown)
	{
		if (t_value < t_max)
		{
			view.move(0, 2.0f);
			t_value++;
		}
	}
	else
	{
		if (t_value > t_max)
		{
			view.move(0, -2.0f);
			t_value--;
		}
	}

	if (moveRight)
	{
		if (r_value < r_max)
		{
			view.move(2.0f, 0);
			r_value++;
		}
	}
	else
	{
		if (r_value > r_max)
		{
			view.move(-2.0f, 0);
			r_value--;
		}
	}

	if (t_value == t_max && r_value == r_max)
	{
		doEvents = true;
	}
}

LevelImporter* l;

GameLoop::GameLoop(Context* c)
{
	this->context = c;
	l = new LevelImporter();
	l->Import("./Resources/levels/Level_New.json");
	l->Prepare();
}

GameLoop::~GameLoop()
{
}

void GameLoop::run()
{
	//context->allUnits.at(0)
	sf::FloatRect rect(0, 0, 960, 640);
	sf::View view;
	view.reset(rect);
	context->window.setView(view);
	//l->Start(context->allUnits.at(0));
	l->Start(context->player);

	sf::Clock deltaClock;

	while (context->window.isOpen()) {
		context->window.clear();

		sf::Time deltaTime = deltaClock.restart();

		//sf::Vector2f s = context->allUnits.at(0)->positions;
		sf::Vector2i worldPos = context->window.mapCoordsToPixel(context->player->positions);

		sf::Event event;
		l->Draw(&context->window);
		l->Update();
	
		MoveView(view);

		if (doEvents) {
			while (context->window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					context->window.close();
			}

			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
			{
				Input::EventOccured(event);

				context->playerInput.CatchInput();
				context->playerMovement.SetActiveKeys(context->playerInput.GetActiveKeys());
				context->playerMovement.Move(deltaTime.asMicroseconds());
			}

			updateViewPort(worldPos);
		}

		context->window.draw(context->player->drawBehaviour->getCurrentImage());

		context->window.setView(view);
		context->window.display();
		context->window.clear();
	}
}
