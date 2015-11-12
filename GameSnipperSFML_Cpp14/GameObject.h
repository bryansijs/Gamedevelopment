#pragma once
#include <string>
#include <vector>
#include <SFML\Graphics.hpp>
#include <iostream>

class DrawContainer;
class MoveContainer;
class DrawBehaviour;
class MoveBehaviour;
class Tile;

class GameObject
{
public:
	GameObject(DrawContainer *drawContainer, std::string textureUrl);
	GameObject();
	~GameObject();

	std::string name;
	std::string type;

	DrawContainer* drawContainer;
	MoveContainer* moveContainer;
	DrawBehaviour* drawBehaviour;
	MoveBehaviour* moveBehaviour;

	sf::Vector2f position;

	void setPosition(sf::Vector2f position) { this->position = position; };
	virtual void Update();

	void setDrawBehaviour(DrawBehaviour* newDrawBehaviour);
	void SetMoveBehaviour(MoveBehaviour* moveBehaviour);

	void setDrawContainer(DrawContainer* newDrawContainer) {this->drawContainer = newDrawContainer	;}
	void setMoveContainer(MoveContainer* newMoveContainer) { this->moveContainer = newMoveContainer; }
	sf::IntRect imageRect =  sf::IntRect(0, 0, 0, 0);

	int xIndex = 0;
	int yIndex = 0;
	int width = 0;
	int height = 0;

	void setImageX(int x)
	{
		this->xIndex = x;
	}

	void setImageY(int y)
	{
		this->yIndex = y;
	}

	int getImageY() { return yIndex * height; }
	int getImageX() { return xIndex * width; }

	void setSize(int width, int height)
	{
		this->width = width;
		this->height = height;
		imageRect.height = height;
		imageRect.width = width;
	}

	bool isColliding(std::vector<Tile> tiles, float newX, float newY);
};

