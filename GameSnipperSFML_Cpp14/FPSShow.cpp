#include "stdafx.h"
#include "FPSShow.h"
#include <string>

#include "Time.h"
FPSShow::FPSShow()
{
	if (!font.loadFromFile("./Resources/moonhouse.ttf"))
	{
		
	}

	fps.setFont(font);
	fps.setCharacterSize(16);
	fps.setColor(sf::Color::Yellow);

	rect.setFillColor(sf::Color(0, 0, 0, 200));
	rect.setSize(sf::Vector2f(100, 20));
}


FPSShow::~FPSShow()
{
}


void FPSShow::draw(sf::RenderWindow &window) {
	window.draw(rect);
	window.draw(fps);
}
void FPSShow::setFPS(float levelx, float  levely, float  width, float  height)
{


	float x = levelx + width - 100;
	float y = levely + 0;
	rect.setPosition(x, y);
	fps.setString("FPS: " + std::to_string(Time::GetFPs()) );

	fps.setPosition(x + 5 ,y +1 );
}