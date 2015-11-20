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
#include "GameObjectFactory.h"

class DrawContainer;

class LevelImporter
{
protected:
	sf::SoundBuffer sbuffer;
	sf::Sound music;
public:
	LevelImporter(DrawContainer *drawContainer);
	LevelImporter(DrawContainer *drawContainer, UseContainer *useContainer);
	LevelImporter();
	~LevelImporter();

	void Import(std::string JSON);
	void Prepare();

	void Clear();

	Level* LevelImporter::getLevel();

private:
	GameObjectFactory* objectFactory;
	void PrepareGameObjects();
	void PrepareTileSets();
	void PrepareTiles();
	void PrepareMusic(std::string musicName);
	void addTile(int dataIndex, Json::Value& value, int i, int j);
	int tileSize;
	int levelHeight;
	int levelWidht;
	sf::IntRect subRect;
	std::map<std::string, std::string> JSONtoMap(Json::Value& properties);

	DrawContainer *drawContainer;
	MoveContainer *moveContainer;
	UseContainer *useContainer;

	std::vector<GameObject*> game_objects;
	std::vector<Tile> tiles;
	std::vector<TileSet> tileSets;

	std::map<int, bool> hazardMap;
};
