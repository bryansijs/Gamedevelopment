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

	sf::IntRect imageRect =  sf::IntRect(0, 0, 0, 0);

	int x_index = 0;
	int y_index = 0;
	int width = 0;
	int height = 0;

	void set_Image_x(int x)
	{
		this->x_index = x;
	}

	void set_Image_y(int y)
	{
		this->y_index = y;
	}

	int get_Image_y() { return y_index * height; }
	int get_Image_x() { return x_index * width; }

	void setSize(int width, int height)
	{
		this->width = width;
		this->height = height;
		imageRect.height = height;
		imageRect.width = width;
	}

	bool isone = false;
	bool isColliding(std::vector<Tile> tiles, float newX, float newY);
};

