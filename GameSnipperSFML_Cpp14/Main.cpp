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
{/*


	sf::Texture bulletTexture;
	bulletTexture.loadFromFile("Resources/sprites/bullet.png");
	sf::Sprite shapey(bulletTexture);

	int bulletSpeed(20);
	sf::Sprite bulletList[10];


	*


	/*
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

	*/
	LevelImporter l;

	//sf::Keyboard::Key d = sf::Keyboard::Key();


	
	return 0;
}

