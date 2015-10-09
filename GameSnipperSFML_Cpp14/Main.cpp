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


int _tmain(int argc, _TCHAR* argv[])
{
	LevelImporter* l = new LevelImporter();
	l->Import("./Resources/levels/Level_New.json");

	l->Prepare();

	sf::RenderWindow window(sf::VideoMode(960, 640), "Team Echo!");

	int value = 0;
	int max = 0;
	sf::FloatRect rect(value, 0, 960, 640);
	sf::View view;
	view.reset(rect);
	bool moveDown = true;

	window.setView(view);

	while (window.isOpen())
	{
		window.clear();

		l->Teken(&window);

		if (moveDown)
		{
			if (value < max)
			{
				view.move(0, 2.0f);
				value++;
			}
		}
		else
		{
			if (value > max)
			{
				view.move(0, -2.0f);
				value--;
			}
		}
		

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				max += 320;
				moveDown = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				max -= 320;
				moveDown = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				for (int i = 0; i < l->getObject().size(); i++)
				{
					l->ObjectOfEnemy(i);
					cout << l->getThis(i)->name << endl;
				}
			}
		}
		window.setView(view);
		window.display();
	}
		
	return 0;
}

