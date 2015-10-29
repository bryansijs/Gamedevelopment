#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

class DrawBehaviour;

class DrawContainer
{
public:
	DrawContainer();
	~DrawContainer();

	void Draw(sf::RenderWindow* window);
	void AddBehaviour(DrawBehaviour* behaviour);
	void RemoveBehaviour(DrawBehaviour* behaviour);
private:
	std::vector<DrawBehaviour*> behaviours;
};

