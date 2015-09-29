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


game_state coreState;
bool quitGame = false;



int _tmain(int argc, _TCHAR* argv[])
{


	sf::Texture bulletTexture;
	bulletTexture.loadFromFile("Resources/sprites/bullet.png");
	sf::Sprite shapey(bulletTexture);

	int bulletSpeed(20);
	sf::Sprite bulletList[10];



	sf::RenderWindow window(sf::VideoMode(640, 480), "Team Echo!");


	coreState.SetWindow(&window);
	coreState.SetState(new test_state());


	sf::Texture menuTexture;
	menuTexture.loadFromFile("Resources/background/backgroundd.png");

	sf::CircleShape shape(100.f);
	shape.setPosition(400, 100);
	sf::Font font;
	font.loadFromFile("Resources/arial.ttf");
	shape.setFillColor(sf::Color::Cyan);
	std::cout << "Debug menu laat fouten zien." << std::endl;

	sf::Text text;
	sf::Music Music1;

	if (!Music1.openFromFile("Resources/music/overworld.ogg"))
	{
		std::cout << "Music not found" << std::endl;
	}
	
	//Music1.play();
	// select the font
	text.setFont(font); // font is a sf::Font
	text.setPosition(180, 160);
	// set the string to display
	text.setString("Welcome team\nEcho");
	// set the character size
	text.setCharacterSize(24); // in pixels, not points!
	// set the color
	text.setColor(sf::Color::White);
	text.setRotation(20);
	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);


	LevelImporter l;

	sf::Keyboard::Key d = sf::Keyboard::Key();
	while (window.isOpen())
	{

		sf::Sprite sprite(menuTexture);
 
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
				{
					shape.setFillColor(sf::Color::Cyan);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
				{
					shape.setFillColor(sf::Color::White);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
				{
					shape.setFillColor(sf::Color::Red);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
				{
					shape.setFillColor(sf::Color::Green);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
				{
					shape.setFillColor(sf::Color::Yellow);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
				{
					shape.setFillColor(sf::Color::Blue);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
				{
					shape.setFillColor(sf::Color::Black);
				}


				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{

					for (int i = 0; i < 10; i++)
					{
						if (bulletList[i].getPosition().x < 0)
						{
							bulletList[i].setTexture(bulletTexture);
							bulletList[i].setPosition(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius() / 2);
					
							break;
						}
					}

				}


			}
		}



		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		for (int i = 0; i < 9; i++)
		{
			if (bulletList[i].getPosition().x >= 0)
			{
				bulletList[i].setPosition(bulletList[i].getPosition().x + bulletSpeed, bulletList[i].getPosition().y);

				if (bulletList[i].getPosition().x > window.getSize().x)
				{
					bulletList[i].setPosition(-100, -100);
				}
			}
		}


		window.clear();

	
		window.draw(sprite);
		window.draw(shape);
		window.draw(text);

		coreState.Update();
		coreState.Render();

		for (int i = 0; i < 9; i++)
		{
			if (bulletList[i].getPosition().x >= 0)
			{
				window.draw(bulletList[i]);
			}
		}

		window.display();

	
	}

	
	return 0;
}

