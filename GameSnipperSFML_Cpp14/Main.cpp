// GameSnippet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "game_state.h"
#include "test_state.h"
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono> 
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2d/Box2D.h>
#include "LevelImporter.h"
#include <string>


game_state coreState;
bool quitGame = false;
using namespace std;

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



int _tmain(int argc, _TCHAR* argv[])
{
	LevelImporter* l = new LevelImporter();
	l->Import("./Resources/levels/Level_New.json");

	l->Prepare();

	sf::RenderWindow window(sf::VideoMode(960, 640), "Team Echo!");


	sf::FloatRect rect(0, 0, 960, 640);
	sf::View view;


	sf::CircleShape shape(25.0f);
	shape.setFillColor(sf::Color::Magenta);
	shape.setPosition(50, 50);

	view.reset(rect);

	window.setView(view);

	while (window.isOpen())
	{
		window.clear();

		l->Draw(&window);

		MoveView(view);
		
		sf::Vector2f s = shape.getPosition();
		sf::Vector2i worldPos = window.mapCoordsToPixel(s);

		sf::Event event;

		if (doEvents) {
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				{
					t_max += 160;
					moveDown = true;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					t_max -= 160;
					moveDown = false;
				}


				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					shape.setPosition(shape.getPosition().x, shape.getPosition().y - 10);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					shape.setPosition(shape.getPosition().x, shape.getPosition().y + 10);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					shape.setPosition(shape.getPosition().x - 10, shape.getPosition().y);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					shape.setPosition(shape.getPosition().x + 10, shape.getPosition().y);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
					cout << "x: " << worldPos.x << " y: " << worldPos.y << endl;

				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					for (int i = 0; i < l->getObject().size(); i++)
					{
						l->ObjectOfEnemy(i);
						cout << l->getThis(i)->name << endl;
					}
				}

				updateViewPort(worldPos);
			}
		}

		window.setView(view);

		window.draw(shape);

		window.display();
	}
		
	return 0;
}

