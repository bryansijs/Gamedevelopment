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

#include "TileSet.h"
#include "Level.h"
#include "GameObjectFactory.h"

class Tile;
class DrawContainer;

class LevelImporter
{
protected:
	sf::SoundBuffer sbuffer;
	sf::Sound music;
public:

	//LevelImporter(DrawContainer *drawContainer, b2World* world);
	//LevelImporter(DrawContainer *drawContainer, GameObjectContainer *gameObjectContainer, b2World* world);

	//LevelImporter(DrawContainer *drawContainer);
	//LevelImporter(DrawContainer *drawContainer, MoveContainer *moveContainer);
	//LevelImporter(DrawContainer *drawContainer, GameObjectContainer *gameObjectContainer);

	LevelImporter(DrawContainer *drawContainer, MoveContainer *moveContainer, GameObjectContainer *gameObjectContainer, b2World* world);

	~LevelImporter();

	bool Import(std::string JSON);
	void Prepare();
	bool PrepareMusic(std::string musicName);
	sf::Sound getMusic() { return music; };

	void Clear();

	Level* LevelImporter::getLevel();

private:
	GameObjectFactory* objectFactory;
	void PrepareGameObjects();
	void PrepareTileSets();
	void PrepareTiles();

	Tile* addTile(int dataIndex, Json::Value& value, int i, int j);
	void addTileToContainer(Tile* tile);

	int tileSize;
	int levelHeight;
	int levelWidht;
	sf::IntRect subRect;
	std::map<std::string, std::string> JSONtoMap(Json::Value& properties);

	DrawContainer *drawContainer;
	MoveContainer *moveContainer;
	GameObjectContainer *gameObjectContainer;

	std::vector<GameObject*> game_objects;
	std::vector<Tile*> groundTiles;
	std::vector<Tile*> roofTiles;
	std::vector<Tile*> tiles;
	std::vector<TileSet*> tileSets;

	std::map<int, bool> hazardMap;
	b2World* world;
};
