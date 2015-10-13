#pragma once

#include "stdafx.h"
#include <json\json.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>
#include <typeinfo>

class LevelImporter
{
public:
	LevelImporter();
	~LevelImporter();
	void Draw(sf::RenderWindow* window);
	void Import(std::string JSON);
	void Prepare();
	void Update();
	void Start(sf::CircleShape* player);
	void setHazardState(int hazardIndex, bool hazardState);
	void setLayerVisibility(int layerIndex, bool isVisible);

	//Tijdelijke Objecten Struct Deze zullen compleet verdwijnen als de baseGame objecten ofzijns
	struct t_Object
	{

		t_Object()
		{
		}
		~t_Object()
		{

		}

		std::string name;
		std::string type;
		sf::Color color;
		int x_loc;
		int y_loc;

	//	sf::CircleShape looks;


		sf::RectangleShape looks;
		virtual void print()
		{
			std::cout << "Object: " << name << std::endl;
		}

		sf::RectangleShape getShape()
		{
			return looks;
		}

		void setSize(int widht, int height)
		{
			looks = sf::RectangleShape(sf::Vector2f(widht, height));
			looks.setFillColor(color);
		}

		void setPosition(int x, int y)
		{
			x_loc = x;
			y_loc = y;
			looks.setPosition(x_loc, y_loc);
		
		}

		void Update()
		{
			setPosition(x_loc, y_loc);
		}
	};

	struct t_Enemy : t_Object
	{
		std::string extra;

		

		t_Enemy()
		{
			color = sf::Color::Green;
		}
	};

	struct t_Door : t_Object
	{
		t_Door()
		{
			color = sf::Color::Yellow;
		}
	};
	struct t_Switch : t_Object
	{
		t_Switch()
		{
			color =sf::Color::Blue;
		}
	};

	struct t_StartTile : t_Object
	{
		t_StartTile()
		{
			color =  sf::Color::Cyan;
		}
	};
	struct t_EndTile : t_Object
	{
		t_EndTile()
		{
			color = sf::Color::White;
		}
	};

	struct t_WarpTile : t_Object
	{
		t_WarpTile()
		{
			color =sf::Color::Red;
		}
	};
	//Tijdelijke objecten functies ombouwen naar de base
	std::vector<t_Object*> game_objects;

	std::vector<t_Object*> getGame_Objects() { return game_objects; }
	t_Object* getObject(int i) { return game_objects.at(i); }

	std::string getObjectType(int i)
	{
		if (dynamic_cast<t_Enemy*> (getObject(i)))
			return "Enemy";
		if (dynamic_cast<t_Door*> (getObject(i)))
			return "Door";
		if (dynamic_cast<t_Switch*> (getObject(i)))
			return "Switch";
		if (dynamic_cast<t_EndTile*> (getObject(i)))
			return "EndTile";
		if (dynamic_cast<t_WarpTile*> (getObject(i)))
			return "WarpTile";
		if (dynamic_cast<t_StartTile*> (getObject(i)))
			return "StartTile";

		return "Object";
	}

	//Tijdelijk Objecten voorbij



private:
	void PrepareGameObjects();
	void PrepareTileSets();
	void PrepareTiles();

	int tileSize;
	int levelHeight;
	int levelWidht;
	sf::IntRect subRect;




};

