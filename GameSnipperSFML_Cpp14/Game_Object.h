#pragma once
#include <string>
#include <vector>
#include <SFML\Graphics.hpp>
#include <iostream>

class DrawBehaviour;

class Game_Object
{
public:
	Game_Object(std::vector<DrawBehaviour*>* draws, std::string textureUrl);
	Game_Object();
	~Game_Object();

	std::string name;
	std::string type;

	DrawBehaviour* drawBehaviour;
	std::vector<DrawBehaviour*>* allDrawBehaviours;

	sf::Vector2f position;

	void setPosition(sf::Vector2f position) { this->position = position; };

	virtual void Update();
	void setDrawBehaviour(DrawBehaviour* newDrawBehaviour);

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
	int get_Image_x() { return  x_index * width;	}

	void setSize(int width, int height)
	{
		this->width = width;
		this->height = height;
		imageRect.height = height;
		imageRect.width = width;
	}

};

