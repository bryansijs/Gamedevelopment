#include <SFML\Graphics.hpp>
#include "stdafx.h"
#include "GameLoop.h"
#include "Context.h"
#include "Unit.h"
#include "DrawBehaviour.h"
#include "NormalDrawBehaviour.h"
#include "MoveBehaviour.h"
#include "LevelImporter.h"

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
	l->Start(context->allUnits.at(0));


	while (context->window.isOpen()) {
		context->window.clear();

		sf::Vector2f s = context->allUnits.at(0)->positions;
		sf::Vector2i worldPos = context->window.mapCoordsToPixel(s);


		sf::Event Event;
		l->Draw(&context->window);
		l->Update();
	
		MoveView(view);

		if (doEvents) {
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

			updateViewPort(worldPos);
		}


		context->window.setView(view);
		context->window.display();
		context->window.clear();

	}
}
