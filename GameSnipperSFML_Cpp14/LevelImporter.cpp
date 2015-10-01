#include "stdafx.h"
#include "LevelImporter.h"
#include <json\json.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>
#define JSON_DLL

using namespace std;

sf::RenderWindow* window;

struct tileSets
{
	int firstgrid;
	int imageheight;
	int imagewidth;
	int tilecounts;
	int tilesize;
	sf::Texture tileImage;
};


struct  tile
{
	sf::Sprite sprite;
	int tilelaag; 
	int x; 
	int y; 
};

std::vector<tile> tegel;
std::ifstream st;
std::vector<tileSets> tileset;
bool parsingSuccessful = false;
Json::Reader reader;
Json::Value root;


void LevelImporter::Prepare()
{
	int tilesize = root["tilewidth"].asInt();
	int levelheight = root["height"].asInt();
	int levelwidht = root["width"].asInt();

	sf::IntRect subRect;
	subRect.width = tilesize;
	subRect.height = tilesize;

	for (Json::Value::iterator it = root["tilesets"].begin(); it != root["tilesets"].end(); ++it)
	{
		Json::Value value = (*it);

		tileSets t;
		t.firstgrid = value["firstgid"].asInt();
		t.imageheight = value["imageheight"].asInt();
		t.imagewidth = value["imagewidth"].asInt();
		t.tilecounts = value["tilecount"].asInt();
		t.tilesize = value["tilewidth"].asInt();
		t.tileImage.loadFromFile(value["image"].asString());

		tileset.push_back(t);
	}

	for (Json::Value::iterator it = root["layers"].begin(); it != root["layers"].end(); ++it)
	{
		Json::Value value = (*it);

		const Json::Value array = value["data"];

		int indentifier = 0;
		//Moet variable worden;
		typedef	std::vector<std::vector<int> > temp_vector;

		temp_vector temp_array(levelheight, vector<int>(levelwidht));

		for (int i = 0; i < levelheight; i++)
			for (int j = 0; j < levelwidht; j++)
			{

				temp_array[i][j] = array[indentifier].asInt();
				indentifier++;
			}

		for (int i = 0; i < levelheight; i++)
			for (int j = 0; j < levelwidht; j++)
			{
				int tileSetIndex = 0;
				int tileStartIndex = 0;

				int temp_int = temp_array[i][j];

				for (size_t tileIndex = 0; tileIndex < tileset.size(); tileIndex++)
				{
					if (temp_int >= tileset[tileIndex].firstgrid && temp_int < (tileset[tileIndex].firstgrid + tileset[tileIndex].tilecounts))
					{
						tileSetIndex = tileIndex;
						tileStartIndex = tileset[tileIndex].firstgrid;
						break;
					}
				}

				int widht_tileCount = tileset[tileSetIndex].imagewidth / tileset[tileSetIndex].tilesize;

				if (temp_int == 0)
					continue;

				int topindex = (temp_int - tileStartIndex) / (widht_tileCount);

				int leftindex = (temp_int - tileStartIndex) - (widht_tileCount * topindex);

				tile tegeltje;

				tegeltje.sprite = sf::Sprite(tileset[tileSetIndex].tileImage);

				subRect.left = (leftindex)* tilesize;
				subRect.top = topindex * tilesize;
				tegeltje.sprite.setTextureRect(subRect);
				tegeltje.sprite.setPosition(float(j*tilesize), float(i*tilesize));

				tegeltje.y = j;
				tegeltje.x = i;
				tegeltje.tilelaag = tileSetIndex;

				tegel.push_back(tegeltje);
			}


	}
}

void LevelImporter::Import(std::string JSON)
{
		st.open(JSON, std::ifstream::binary);

	bool parsingSuccessful = reader.parse(st, root, false);
	if (!parsingSuccessful)
	{
		std::cout << reader.getFormattedErrorMessages() << "\n";
	}
}

void LevelImporter::Teken(sf::RenderWindow* window)
{
	for (size_t i = 0; i < tegel.size(); i++)
		window->draw(tegel.at(i).sprite);
}


LevelImporter::LevelImporter()
{




}


LevelImporter::~LevelImporter()
{
}
#undef JSON_DLL