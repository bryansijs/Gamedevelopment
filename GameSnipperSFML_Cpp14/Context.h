#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include <Awesomium/WebCore.h>

class Unit;

class Context
{
public:
	Context(int screenWidth, int screenHeight);
	~Context();

	sf::RenderWindow window;

	std::vector<Unit*> allUnits;
	std::vector<Unit*> getUnits() { return allUnits; };
	Awesomium::WebCore* web_core;
	Unit* getUnitAt(int i) { return allUnits.at(i); };
private:
	sf::Vector2i* screenDimensions;
	sf::Clock clock;

	
};

