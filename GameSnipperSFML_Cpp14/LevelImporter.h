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
#include "GameObject.h"
#include <Box2D/Box2D.h>
#include "Tile.h"
#include "TileSet.h"
#include "Level.h"

class DrawContainer;

class LevelImporter
{
protected:
	sf::SoundBuffer sbuffer;
	sf::Sound music;
public:
	LevelImporter(DrawContainer *drawContainer);
	LevelImporter();
	~LevelImporter();

	void Import(std::string JSON);
	void Prepare();

	void Clear();
	std::vector<GameObject*> game_objects;

	std::vector<Tile> tiles;
	std::vector<TileSet> tileSets;

	DrawContainer *drawContainer;

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
