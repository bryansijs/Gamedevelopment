#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

class DrawBehaviour;

class DrawContainer
{
public:
	DrawContainer();
	~DrawContainer();

	void Draw(sf::RenderWindow* window, sf::Vector2f viewPortPosition);
	void AddBehaviour(DrawBehaviour* behaviour);
	void RemoveBehaviour(DrawBehaviour* behaviour);
private:
	std::vector<DrawBehaviour*> behaviours;
};

