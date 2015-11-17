#pragma once
#include "stdafx.h"
#include "LevelImporter.h"

#include "DrawContainer.h"
#include "NormalDrawBehaviour.h"
#include "StartTile.h"
#include "Door.h"
#include "Game_Switch.h"
#include "WarpTile.h"
#include "EndTile.h"
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

		TileSet tileset;
		tileset.firstGrid = value["firstgid"].asInt();
		tileset.imageHeight = value["imageheight"].asInt();
		tileset.imageWidth = value["imagewidth"].asInt();
		tileset.tileAmount = value["tilecount"].asInt();
		tileset.tileSize = value["tilewidth"].asInt();
		tileset.tileImage.loadFromFile("./Resources/tiles/" + value["name"].asString() + ".png");

		tileSets.push_back(tileset);
	}
}

enum string_code {
	s_Enemy,
	s_Switch,
	s_Door,
	s_StartTile,
	s_EndTile,
	s_WarpTile
};

string_code hashit(std::string const& inString) {
	if (inString == "Enemy") return s_Enemy;
	if (inString == "Switch") return s_Switch;
	if (inString == "Door") return s_Door;
	if (inString == "StartTile") return s_StartTile;
	if (inString == "EndTile") return s_EndTile;
	if (inString == "WarpTile") return s_WarpTile;
}

void LevelImporter::PrepareGameObjects()
{
	for (Json::Value::iterator it = jsonRoot["layers"].begin(); it != jsonRoot["layers"].end(); ++it)
	{
		Json::Value value = (*it);

		if (value.isMember("objects"))
		{
			int qi = 0;
			for (Json::Value::iterator object = value["objects"].begin(); object != value["objects"].end(); ++object)
			{
				Json::Value val = (*object);
				int x, y, widht, height;

				switch (hashit(val["type"].asString()))
				{

				case s_Enemy:
				{
					std::string v = val["type"].asString();
					std::string imgurl = val["properties"]["image"].asString();
					GameObject *enemy = new GameObject(drawContainer, imgurl);
					x = val["x"].asInt();
					y = val["y"].asInt();

					widht = val["width"].asInt();
					height = val["height"].asInt();
					enemy->setPosition(sf::Vector2f(x, y));
					enemy->setSize(widht, height);
					enemy->set_Image_x(qi);
					enemy->set_Image_y(qi);
					qi++;
					game_objects.push_back(enemy);

					break;
				}
				case s_EndTile:
				{
					EndTile * endTile = new EndTile();
					x = val["x"].asInt();
					y = val["y"].asInt();
					widht = val["width"].asInt();
					height = val["height"].asInt();

					endTile->setSize(widht, height);
					game_objects.push_back(endTile);
					break;
				}

				case s_WarpTile: {
					WarpTile *warpTile = new WarpTile();
					x = val["x"].asInt();
					y = val["y"].asInt();
					widht = val["width"].asInt();
					height = val["height"].asInt();
					warpTile->setPosition(sf::Vector2f(x, y));
					warpTile->setSize(widht, height);
					game_objects.push_back(warpTile);
					break;
				}



				case s_StartTile:
				{
					StartTile *startTile = new StartTile();
					x = val["x"].asInt();
					y = val["y"].asInt();
					widht = val["width"].asInt();
					height = val["height"].asInt();
					startTile->setPosition(sf::Vector2f(x, y));
					game_objects.push_back(startTile);
					break;
				}

				case s_Switch:
				{
					Game_Switch *_Switch = new Game_Switch();
					x = val["x"].asInt();
					y = val["y"].asInt();
					widht = val["width"].asInt();
					height = val["height"].asInt();
					_Switch->setPosition(sf::Vector2f(x, y));
					_Switch->setSize(widht, height);
					game_objects.push_back(_Switch);
					break;
				}

				case s_Door:
				{
					Door *door = new Door();
					x = val["x"].asInt();
					y = val["y"].asInt();
					widht = val["width"].asInt();
					height = val["height"].asInt();
					door->setPosition(sf::Vector2f(x, y));
					door->setSize(widht, height);
					game_objects.push_back(door);

				}



				default:
				{
					std::string imgurl = val["properties"]["image"].asString();

					GameObject* Object = nullptr;
					if (imgurl == "")
					{
						Object = new GameObject();
					}
					else
					{
						Object = new GameObject(drawContainer, imgurl);
					}

					x = val["x"].asInt();
					y = val["y"].asInt();
					widht = val["width"].asInt();
					height = val["height"].asInt();
					Object->setPosition(sf::Vector2f(x, y));
					Object->setSize(widht, height);
					game_objects.push_back(Object);
					break;
				}
				}
			}

		}
	}
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

		for (int i = 0; i < levelHeight; i++)
		{
			for (int j = 0; j < levelWidht; j++)
			{
				data_vector[i][j] = temp_data_array[indentifier].asInt();
				indentifier++;
			}
		}

		for (int i = 0; i < levelHeight; i++)
			for (int j = 0; j < levelWidht; j++)
			{
				int tileSetIndex = 0;
				int tileStartIndex = 0;

				//Deze integer bevat welke tile getekend moet worden vanuit tiled;
				int data_index = data_vector[i][j];

				if (data_index == 0)
					continue;

				for (size_t tileIndex = 0; tileIndex < tileSets.size(); tileIndex++)
				{
					if (data_index >= tileSets[tileIndex].firstGrid && data_index < (tileSets[tileIndex].firstGrid + tileSets[tileIndex].tileAmount))
					{
						tileSetIndex = tileIndex;
						tileStartIndex = tileSets[tileIndex].firstGrid;
						break;
					}
				}

				int tileCount_widht = tileSets[tileSetIndex].imageWidth / tileSets[tileSetIndex].tileSize;
				int topIndex = (data_index - tileStartIndex) / (tileCount_widht);
				int leftIndex = (data_index - tileStartIndex) - (tileCount_widht * topIndex);

				Tile insert_tile;

				insert_tile.sprite = sf::Sprite(tileSets[tileSetIndex].tileImage);

				subRect.left = (leftIndex)* tileSize;
				subRect.top = topIndex * tileSize;
				insert_tile.sprite.setTextureRect(subRect);
				insert_tile.sprite.setPosition(float(j*tileSize), float(i*tileSize));

				insert_tile.y_Position = i*tileSize;
				insert_tile.x_Position = j*tileSize;
				insert_tile.tileLayer = tileSetIndex;

				if (value["visible"].asString() == "true")
					insert_tile.isVisible = true;
				else
					insert_tile.isVisible = false;

				insert_tile.isCollidable = false;
				insert_tile.isHazard = false;
				insert_tile.hazardState = false;
				insert_tile.hazardValue = 0;
				insert_tile.hazardIndex = 0;

				if (value.isMember("properties"))
				{
					Json::Value props = value["properties"];

					if (props.isMember("isCollidable"))
					{
						if (value["properties"]["isCollidable"].asString() == "true")
						{
							insert_tile.isCollidable = true;
							insert_tile.bodyDef = new b2BodyDef();

							insert_tile.bodyDef->type = b2_staticBody;
							insert_tile.bodyDef->position.Set(insert_tile.x_Position, insert_tile.y_Position);
						}
					}

					if (props.isMember("isEnemyCollidable"))
					{
						if (value["properties"]["isEnemyCollidable"].asString() == "true")
						{
							insert_tile.isEnemyCollidable = true;
							insert_tile.enemyBodyDef = new b2BodyDef();

							insert_tile.enemyBodyDef->type = b2_staticBody;
							insert_tile.enemyBodyDef->position.Set(insert_tile.x_Position, insert_tile.y_Position);
						}
					}

					if (props.isMember("isHazard"))
					{
						if (value["properties"]["isHazard"].asString() == "true")
							insert_tile.isHazard = true;
					}

					if (props.isMember("hazardState"))
					{
						if (value["properties"]["hazardState"].asString() == "true")
							insert_tile.hazardState = true;
					}

					if (props.isMember("hazardIndex"))
					{
						string hazardIndex = value["properties"]["hazardIndex"].asString();
						insert_tile.hazardIndex = atoi(hazardIndex.c_str());
					}

					if (props.isMember("hazardValue"))
					{
						string hazardValue = value["properties"]["hazardValue"].asString();
						insert_tile.hazardValue = atoi(hazardValue.c_str());
					}

					if (props.isMember("hazardType"))
					{
						string hazardType = value["properties"]["hazardType"].asString();
						insert_tile.hazardType = atoi(hazardType.c_str());
					}

					if (props.isMember("music"))
					{
						musicName = value["properties"]["music"].asString();
					}
				}

				tiles.push_back(insert_tile);
			}
	}
}

bool LevelImporter::PrepareMusic(string music)
{
	if (sbuffer.loadFromFile("./Resources/music/" + music))
	{
		this->music.setBuffer(sbuffer);
		return true;
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
	PrepareGameObjects();
	PrepareTiles();
	PrepareMusic(musicName);
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
	Level* level = new Level();
	level->setGameObjects(game_objects);
	level->setTileSets(tileSets);
	level->setTiles(tiles);
	level->setMusic(music);

	return level;
}

LevelImporter::LevelImporter(DrawContainer *drawContainer)
{
	this->drawContainer = drawContainer;
}

LevelImporter::LevelImporter()
{
}

LevelImporter::~LevelImporter()
{

}
#undef JSON_DLL