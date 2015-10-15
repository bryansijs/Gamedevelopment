#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
class MoveBehaviour;
class DrawBehaviour;
class Unit;

class Context
{
public:
	Context(int screenHeight, int screenWidth);
	~Context();

	sf::RenderWindow window;
	std::vector<MoveBehaviour*> allMoveBehaviours;
	std::vector<DrawBehaviour*> allDrawBehaviours;
	std::vector<Unit*> allUnits;
	std::vector<Unit*> getUnits() { return allUnits;  };

	Unit* getUnitAt(int i) { return allUnits.at(i); };


private:
	sf::Vector2i* screenDimensions;
	sf::Clock clock;

};

