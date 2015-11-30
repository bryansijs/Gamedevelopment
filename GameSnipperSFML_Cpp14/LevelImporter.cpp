#pragma once
#include "stdafx.h"
#include "LevelImporter.h"
#include "DrawContainer.h"
#include "NormalDrawBehaviour.h"

#define JSON_DLL

using namespace std;

std::ifstream inputFileStream;

bool parsingSuccessful = false;

Json::Reader jsonReader;
Json::Value jsonRoot;
std::string musicName;

void LevelImporter::PrepareTileSets()
{
	for (Json::Value::iterator it = jsonRoot["tilesets"].begin(); it != jsonRoot["tilesets"].end(); ++it)
	{
		Json::Value value = (*it);

		TileSet* tileset = new TileSet();
		tileset->firstGrid = value["firstgid"].asInt();
		tileset->imageHeight = value["imageheight"].asInt();
		tileset->imageWidth = value["imagewidth"].asInt();
		tileset->tileAmount = value["tilecount"].asInt();
		tileset->tileSize = value["tilewidth"].asInt();
		tileset->tileImage.loadFromFile("./Resources/tiles/" + value["name"].asString() + ".png");

		tileSets.push_back(tileset);
	}
}

void LevelImporter::PrepareGameObjects()
{

	objectFactory = new GameObjectFactory(drawContainer,moveContainer, gameObjectContainer);
	objectFactory->setTile(tiles);
	for (Json::Value::iterator it = jsonRoot["layers"].begin(); it != jsonRoot["layers"].end(); ++it)
	{
		Json::Value value = (*it);
		if (value.isMember("objects"))
		{
			for (Json::Value::iterator object = value["objects"].begin(); object != value["objects"].end(); ++object)
			{
				std::map<std::string, std::string> properties = JSONtoMap(*object);
				game_objects.push_back(objectFactory->Create(properties));
			}
		}
	}
}


std::map<std::string, std::string> LevelImporter::JSONtoMap(Json::Value& properties)
{
	std::map<std::string, std::string> values;

	for (Json::Value::iterator object = properties.begin(); object != properties.end(); ++object)
	{
		if (object.key() != "properties")
			values.insert(std::pair<std::string, std::string>(object.key().asString(), (*object).asString()));
		else
		{
			Json::Value props = properties["properties"];
			if (!props.empty())
				for (Json::Value::iterator bobject = props.begin(); bobject != props.end(); ++bobject)
				{
					values.insert(std::pair<std::string, std::string>(bobject.key().asString(), (*bobject).asString()));
				}
		}
	}
	return values;
}

void LevelImporter::PrepareTiles()
{
	for (Json::Value::iterator it = jsonRoot["layers"].begin(); it != jsonRoot["layers"].end(); ++it)
	{
		Json::Value value = (*it);
		Json::Value temp_data_array = value["data"];

		int indentifier = 0;
		typedef	std::vector<std::vector<int>> multi_Vector;

		multi_Vector data_vector(levelHeight, vector<int>(levelWidht));

		for (int y = 0; y < levelHeight; y++)
		{
			for (int x = 0; x < levelWidht; x++)
			{
				data_vector[y][x] = temp_data_array[indentifier].asInt();
				indentifier++;
			}
		}

		for (int y = 0; y < levelHeight; y++)
			for (int x = 0; x < levelWidht; x++)
			{
				//Deze integer bevat welke tile getekend moet worden vanuit tiled;
				int dataIndex = data_vector[y][x];

				if (dataIndex == 0)
					continue;

				addTile(dataIndex, (*it), x, y);
			}
	}
}



void LevelImporter::addTile(int dataIndex, Json::Value& value, int x, int y)
{
	int tileSetIndex = 0;
	int tileStartIndex = 0;

	for (size_t tileIndex = 0; tileIndex < tileSets.size(); tileIndex++)
	{
		if (dataIndex >= tileSets[tileIndex]->firstGrid && dataIndex < (tileSets[tileIndex]->firstGrid + tileSets[tileIndex]->tileAmount))
		{
			tileSetIndex = tileIndex;
			tileStartIndex = tileSets[tileIndex]->firstGrid;
			break;
		}
	}

	int tileCount_widht = tileSets[tileSetIndex]->imageWidth / tileSets[tileSetIndex]->tileSize;
	int topIndex = (dataIndex - tileStartIndex) / (tileCount_widht);
	int leftIndex = (dataIndex - tileStartIndex) - (tileCount_widht * topIndex);

	Tile* insert_tile = new Tile();;

	insert_tile->sprite = sf::Sprite(tileSets[tileSetIndex]->tileImage);

	subRect.left = (leftIndex)* tileSize;
	subRect.top = topIndex * tileSize;
	insert_tile->sprite.setTextureRect(subRect);
	insert_tile->sprite.setPosition(float(x*tileSize), float(y*tileSize));

	insert_tile->y_Position = y*tileSize;
	insert_tile->x_Position = x*tileSize;
	insert_tile->tileLayer = tileSetIndex;

	if (value["visible"].asString() == "true")
		insert_tile->isVisible = true;
	else
		insert_tile->isVisible = false;

	insert_tile->isCollidable = false;
	insert_tile->isHazard = false;
	insert_tile->hazardState = false;
	insert_tile->hazardValue = 0;
	insert_tile->hazardIndex = 0;

	if (value.isMember("properties"))
	{
		Json::Value props = value["properties"];



		if (props.isMember("hazardLinkIndex"))
		{
			string hazardIndex = value["properties"]["hazardLinkIndex"].asString();
			insert_tile->hazardLinkIndex = atoi(hazardIndex.c_str());

		}


		if (props.isMember("isCollidable"))
		{
			if (value["properties"]["isCollidable"].asString() == "true")
			{
				insert_tile->isCollidable = true;
				insert_tile->bodyDef = new b2BodyDef();

				insert_tile->bodyDef->type = b2_staticBody;
				insert_tile->bodyDef->position.Set(insert_tile->x_Position, insert_tile->y_Position);
			}
		}

		if (props.isMember("isEnemyCollidable"))
		{
			if (value["properties"]["isEnemyCollidable"].asString() == "true")
			{
				insert_tile->isEnemyCollidable = true;
				insert_tile->enemyBodyDef = new b2BodyDef();

				insert_tile->enemyBodyDef->type = b2_staticBody;
				insert_tile->enemyBodyDef->position.Set(insert_tile->x_Position, insert_tile->y_Position);
			}
		}

		if (props.isMember("isHazard"))
		{
			if (value["properties"]["isHazard"].asString() == "true")
				insert_tile->isHazard = true;
		}


		if (props.isMember("hazardIndex"))
		{
			string hazardIndex = value["properties"]["hazardIndex"].asString();
			insert_tile->hazardIndex = atoi(hazardIndex.c_str());

			if (!hazardMap.count(insert_tile->hazardIndex))
				hazardMap.insert(std::pair<int, bool>(insert_tile->hazardIndex, false));
		}



		if (props.isMember("hazardState"))
		{
			if (value["properties"]["hazardState"].asString() == "true")
				insert_tile->hazardState = true;

			if (hazardMap.count(insert_tile->hazardIndex)) {
				auto search = hazardMap.find(insert_tile->hazardIndex);
				if (search != hazardMap.end()) {
					if (search->second != insert_tile->hazardState) {
						search->second = insert_tile->hazardState;
					}
				}
			}
		}



		if (props.isMember("hazardValue"))
		{
			string hazardValue = value["properties"]["hazardValue"].asString();
			insert_tile->hazardValue = atoi(hazardValue.c_str());
		}

		if (props.isMember("hazardType"))
		{
			string hazardType = value["properties"]["hazardType"].asString();
			insert_tile->hazardType = atoi(hazardType.c_str());
		}

		if (props.isMember("music"))
		{
			musicName = value["properties"]["music"].asString();
		}
	}

	tiles.push_back(insert_tile);
}

bool LevelImporter::PrepareMusic(string music)
{
	if (music != "")
	{
		if (sbuffer.loadFromFile("./Resources/music/" + music))
		{
			this->music.setBuffer(sbuffer);
			return true;
		}
	}
	
	return false;
}

void LevelImporter::Prepare()
{
	tileSize = jsonRoot["tilewidth"].asInt();
	levelHeight = jsonRoot["height"].asInt();
	levelWidht = jsonRoot["width"].asInt();

	subRect.width = tileSize;
	subRect.height = tileSize;

	PrepareTileSets();

	PrepareTiles();
	PrepareMusic(musicName);
	PrepareGameObjects();
}

bool LevelImporter::Import(std::string JSON)
{
	inputFileStream.open(JSON, std::ifstream::binary);

	bool parsingSuccessful = jsonReader.parse(inputFileStream, jsonRoot, false);
	if (!parsingSuccessful)
	{
		std::cout << jsonReader.getFormattedErrorMessages() << "\n";
		return false;
	}
	return true;
}

void LevelImporter::Clear()
{
	game_objects.clear();
	tileSets.clear();
	tiles.clear();
	music.resetBuffer();
}

Level* LevelImporter::getLevel()
{
	Level* level = new Level(gameObjectContainer);
	level->setGameObjects(game_objects);
	level->setTileSets(tileSets);
	level->setTiles(tiles);
	level->setMusic(music);
	level->setHazardMap(hazardMap);

	return level;
}

LevelImporter::LevelImporter(DrawContainer *drawContainer)
{
	this->drawContainer = drawContainer;
}

LevelImporter::LevelImporter(DrawContainer *drawContainer, GameObjectContainer *gameObjectContainer)
{
	this->drawContainer = drawContainer;
	this->gameObjectContainer = gameObjectContainer;
}

LevelImporter::LevelImporter()
{
}

LevelImporter::~LevelImporter()
{

}
#undef JSON_DLL