#pragma once

#include "stdafx.h"
#include <json\json.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <typeinfo>
#include "Unit.h"
#include <math.h> 
#include "Game_Object.h"
#include <Box2D/Box2D.h>
#include "Tile.h"
#include "TileSet.h"
#include "Level.h"

class LevelImporter
{
protected:
	sf::SoundBuffer sbuffer;
	sf::Sound music;
public:
	LevelImporter(std::vector<DrawBehaviour*> draws);
	LevelImporter();
	~LevelImporter();

	void Import(std::string JSON);
	void Prepare();

	void Clear();
	std::vector<Game_Object*> game_objects;

	std::vector<Tile> tiles;
	std::vector<TileSet> tileSets;
	std::vector<DrawBehaviour*> draws;
	Level* LevelImporter::getLevel();

private:
	void PrepareGameObjects();
	void PrepareTileSets();
	void PrepareTiles();
	void PrepareMusic(std::string musicName);
	int tileSize;
	int levelHeight;
	int levelWidht;
	sf::IntRect subRect;
};
