#include "stdafx.h"
#include "game_state.h"
#include "test_state.h"
#include "LevelImporter.h"
#include "Input.h"
#include "KeyMapping.h"
#include "KeyMappingImporter.h"
#include "PlayerInput.h"

#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono> 
#include <cstdio>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Box2d/Box2D.h>


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
	// TODO: Question about pointer
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
	l->Start(&shape);

	try
	{
		// Generate keymap from json file
		unique_ptr<KeyMappingImporter> keyMappingImporter(new KeyMappingImporter());
		keyMappingImporter->Import("./Resources/key-mapping.json");

		// Save keymap to keymapping
		multimap<string, string> mapping = keyMappingImporter->GetMapping();
		KeyMapping::ReloadMapping(mapping);

		// Create playermovement
		unique_ptr<PlayerInput> playerInput(new PlayerInput());

		while (window.isOpen())
		{
			window.clear();

			l->Draw(&window);
			l->Update();
			MoveView(view);

			sf::Vector2f s = shape.getPosition();
			sf::Vector2i worldPos = window.mapCoordsToPixel(s);

			sf::Event event;

			if (doEvents) {
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();

					if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
					{
						Input::EventOccured(event);

						if (playerInput->MoveEvent())
						{
							
						}
					}

					/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
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

					updateViewPort(worldPos);*/
				}
			}

			//window.setView(view);
			//window.draw(shape);
			//window.display();
		}
	}
	catch (exception e)
	{
		cerr << e.what();
	}
	catch (...)
	{
		cerr << "Default exception";
	}
		
	return 0;
}

