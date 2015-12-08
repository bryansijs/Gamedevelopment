#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include <Awesomium/WebCore.h>
#include <Box2D\Box2D.h>

class Unit;

class Context
{
public:
	Context(int screenWidth, int screenHeight);
	~Context();

	sf::RenderWindow window;

	std::vector<Unit*> allUnits;
	std::vector<Unit*> getUnits() { return allUnits; };

	Unit* getUnitAt(int i) { return allUnits.at(i); };

	Awesomium::WebCore* web_core;
private:
	sf::Vector2i* screenDimensions;
	sf::Clock clock;

	
};

