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
	void setHazardState(int hazardIndex, bool hazardState);
	void setLayerVisibility(int layerIndex, bool isVisible);

	//Tijdelijke Objecten Struct Deze zullen compleet verdwijnen als de baseGame objecten ofzijns
	struct t_Object
	{
		std::string name;
		std::string type;
		int x_loc;
		int y_loc;

		virtual void print()
		{
			std::cout << "Object: " << name << std::endl;
		}
	};

	struct t_Enemy : t_Object
	{
		std::string extra;


		void print() override
		{
			std::cout << "Enemy: " << extra << std::endl;
		}

		void setExtra(std::string e)
		{
			extra = e;
		}

	};

	struct t_Door : t_Object
	{};
	struct t_Switch : t_Object
	{};

	struct t_EndTile : t_Object
	{};

	struct t_WarpTile : t_Object
	{};
	//Tijdelijke objecten functies ombouwen naar de base
	std::vector<t_Object*> objecten;

	std::vector<t_Object*> getObject() { return objecten; }
	t_Object* getThis(int i) { return objecten.at(i); }

	void ObjectOfEnemy(int i)
	{
		objecten.at(i)->print();
	}

	std::string getObjectType(int i)
	{
		if (dynamic_cast<t_Enemy*> (getThis(i)))
			return "Enemy";
		if (dynamic_cast<t_Door*> (getThis(i)))
			return "Door";
		if (dynamic_cast<t_Switch*> (getThis(i)))
			return "Switch";
		if (dynamic_cast<t_EndTile*> (getThis(i)))
			return "EndTile";
		if (dynamic_cast<t_WarpTile*> (getThis(i)))
			return "WarpTile";
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

