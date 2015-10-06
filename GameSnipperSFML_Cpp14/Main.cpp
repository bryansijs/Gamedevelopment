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
	l->Import("./Resources/levels/Level_1.json");

	l->Prepare();

	sf::RenderWindow window(sf::VideoMode(1280, 960), "Team Echo!");

	while (window.isOpen())
	{
		window.clear();

		l->Teken(&window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				l->Update();
			}


		}

		window.display();
	}
		
	return 0;
}

