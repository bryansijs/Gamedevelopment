#include "stdafx.h"
#include "LevelImporter.h"
#include <json\json.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>
#define JSON_DLL

using namespace std;


struct TileSet
{
	int firstGrid;
	int imageHeight;
	int imageWidth;
	int tileAmount;
	int tileSize;
	sf::Texture tileImage;
};

struct  Tile
{
	sf::Sprite sprite;
	int tileLayer;
	int x_Position;
	int y_Position;

	bool isHazard;
	bool hazardState;
	int hazardValue;
	int hazardIndex;
	int hazardType;

	bool isEnemyCollidable;
	bool isCollidable;
	bool isVisible;

	b2BodyDef* bodyDef;
	b2BodyDef* enemyBodyDef;
};

std::vector<Tile> tiles;
std::ifstream inputFileStream;
std::vector<TileSet> tileSets;

bool parsingSuccessful = false;

Json::Reader jsonReader;
Json::Value jsonRoot;


void  LevelImporter::updateViewPort(sf::Vector2i &worldPos)
{
	//updateVP
	if (worldPos.y > 640)
	{
		doEvents = false;
		t_max += 320;
		moveDown = true;
	}

	if (worldPos.y < 0)
	{
		doEvents = false;
		t_max -= 320;
		moveDown = false;
	}

	if (worldPos.x > 960)
	{
		doEvents = false;
		r_max += 480;
		moveRight = true;
	}

	if (worldPos.x < 0)
	{
		doEvents = false;
		r_max -= 480;
		moveRight = false;
	}
}


void LevelImporter::MoveView(sf::View& view)
{
	if (moveDown)
	{
		if (t_value < t_max)
		{
			view.move(0, 2.0f);
			t_value++;
		}
	}
	else
	{
		if (t_value > t_max)
		{
			view.move(0, -2.0f);
			t_value--;
		}
	}

	if (moveRight)
	{
		if (r_value < r_max)
		{
			view.move(2.0f, 0);
			r_value++;
		}
	}
	else
	{
		if (r_value > r_max)
		{
			view.move(-2.0f, 0);
			r_value--;
		}
	}

	if (t_value == t_max && r_value == r_max)
	{
		doEvents = true;
	}
}

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
	Enemy,
	Switch,
	Door,
	StartTile,
	EndTile,
	WarpTile
};

string_code hashit(std::string const& inString) {
	if (inString == "Enemy") return Enemy;
	if (inString == "Switch") return Switch;
	if (inString == "Door") return Door;
	if (inString == "StartTile") return StartTile;
	if (inString == "EndTile") return EndTile;
	if (inString == "WarpTile") return WarpTile;
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
					case Enemy:
					{
						t_Enemy *enemy = new t_Enemy();
						x = val["x"].asInt();
						y = val["y"].asInt();

						widht = val["width"].asInt();
						height = val["height"].asInt();
						enemy->setPosition(x, y);
						enemy->setSize(widht, height);
						game_objects.push_back(enemy);
						qi++;
					}
					break;
					case Switch:
					{
						t_Switch *_Switch = new t_Switch();
						x = val["x"].asInt();
						y = val["y"].asInt();
						widht = val["width"].asInt();
						height = val["height"].asInt();
						_Switch->setPosition(x, y);
						_Switch->setSize(widht, height);
						game_objects.push_back(_Switch);
					}
					break;
					case Door:
					{
						t_Door *Door = new t_Door();
						x = val["x"].asInt();
						y = val["y"].asInt();
						widht = val["width"].asInt();
						height = val["height"].asInt();
						Door->setPosition(x, y);
						Door->setSize(widht, height);
						game_objects.push_back(Door);
					}
					break;
					case StartTile:
					{
						t_StartTile *StartTile = new t_StartTile();
						x = val["x"].asInt();
						y = val["y"].asInt();
						widht = val["width"].asInt();
						height = val["height"].asInt();
						StartTile->setPosition(x, y);
						StartTile->setSize(widht, height);
						game_objects.push_back(StartTile);
					}
					break;
					case EndTile:
					{
						t_EndTile *EndTile = new t_EndTile();
						x = val["x"].asInt();
						y = val["y"].asInt();
						widht = val["width"].asInt();
						height = val["height"].asInt();
						EndTile->setPosition(x, y);
						EndTile->setSize(widht, height);
						game_objects.push_back(EndTile);
					}
					break;
					case WarpTile: {
						t_WarpTile *WarpTile = new t_WarpTile();
						x = val["x"].asInt();
						y = val["y"].asInt();
						widht = val["width"].asInt();
						height = val["height"].asInt();
						WarpTile->setPosition(x, y);
						WarpTile->setSize(widht, height);
						game_objects.push_back(WarpTile);
					}
					break;
					default:
					{
						t_Object *Object = new t_Object();
						x = val["x"].asInt();
						y = val["y"].asInt();
						widht = val["width"].asInt();
						height = val["height"].asInt();
						Object->setPosition(x, y);
						Object->setSize(widht, height);
						game_objects.push_back(Object);
					}
					break;
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

				insert_tile.y_Position = j*tileSize;
				insert_tile.x_Position = i*tileSize;
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
				}

				tiles.push_back(insert_tile);
			}
	}
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
}

void LevelImporter::Start(Unit* player, sf::Vector2u* size)
{

	t_StartTile* start = nullptr;

	for (size_t i = 0; i < getGame_Objects().size(); i++)
	{
		if (dynamic_cast<t_StartTile*> (getObject(i)))
			start = dynamic_cast<t_StartTile*> (getObject(i));
	}

	if (start == nullptr)
	{
		start = new t_StartTile();
		start->x_loc = 25;
		start->y_loc = 25;
	}

	int map_yLocation = start->y_loc / size->y;
	int map_xLocation = start->x_loc / size->x;
	viewPortY = (map_yLocation * size->y);
	viewPortX = (map_xLocation * size->x);

	player->setPosition(start->x_loc, start->y_loc);
}

void LevelImporter::Import(std::string JSON)
{
	inputFileStream.open(JSON, std::ifstream::binary);

	bool parsingSuccessful = jsonReader.parse(inputFileStream, jsonRoot, false);
	if (!parsingSuccessful)
	{
		std::cout << jsonReader.getFormattedErrorMessages() << "\n";
	}
}

void LevelImporter::Draw(sf::RenderWindow* window, sf::View* view)
{
	for (size_t i = 0; i < tiles.size(); i++)
		if (tiles.at(i).isVisible)
			window->draw(tiles.at(i).sprite);

	for (size_t i = 0; i < getGame_Objects().size(); i++)
		window->draw((getObject(i))->getShape());


	MoveView(*view);
}

void LevelImporter::setHazardState(int hazardIndex, bool hazardState)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles.at(i).hazardIndex == hazardIndex)
		{
			tiles.at(i).hazardState = hazardState;
			tiles.at(i).isVisible = !hazardState;
		}
	}
}

void LevelImporter::setLayerVisibility(int layerIndex, bool isVisible)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles.at(i).tileLayer == layerIndex)
			tiles.at(i).isVisible = isVisible;
	}
}

void LevelImporter::Update()
{
	for (size_t i = 0; i < getGame_Objects().size(); i++)
		getObject(i)->Update();
}


LevelImporter::LevelImporter()
{




}


LevelImporter::~LevelImporter()
{

}
#undef JSON_DLL