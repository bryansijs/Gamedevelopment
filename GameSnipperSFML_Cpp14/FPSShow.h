#pragma once
#include "SFML/Graphics.hpp"
class FPSShow
{
private:
	sf::Font font;
	sf::Text fps;
	sf::RectangleShape rect;
public:
	FPSShow();
	~FPSShow();

	void setFPS(float levelx, float  levely, float  width, float  height);
	void draw(sf::RenderWindow &window);
};

