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
	void Teken(sf::RenderWindow* window);
	void 	Import(std::string JSON);
	void Prepare();
	void Update();

	//Tijdelijke Objecten Struct
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

	

	std::vector<t_Object*> objecten;


	std::vector<t_Object*> getObject() { return objecten;}


	t_Object* getThis(int i) { return objecten.at(i); }

	void ObjectOfEnemy(int i)
	{
		objecten.at(i)->print();
		
		if (dynamic_cast<t_Enemy*> (getThis(i))) {
			std::cout << "Enemy" << std::endl;
			std::cout << dynamic_cast<t_Enemy*> (getThis(i))->extra << std::endl;
		}
		else
			std::cout << "Different object" << std::endl;

	}

private :
		sf::RenderWindow window;

	
		

};

