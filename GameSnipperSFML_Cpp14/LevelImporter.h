#pragma once

#include "stdafx.h"
#include <json\json.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>

class LevelImporter
{
public:
	LevelImporter();
	~LevelImporter();
	void Teken(sf::RenderWindow* window);
	void 	Import(std::string JSON);
	void Prepare();
	void Update();
private :
		sf::RenderWindow window;

};

