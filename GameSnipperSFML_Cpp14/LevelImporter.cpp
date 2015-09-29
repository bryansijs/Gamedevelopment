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
};

constexpr int n(int levelheight)
{
	return levelheight;
}


LevelImporter::LevelImporter()
{
	Json::Reader reader;

	std::ifstream st("./Resources/levels/level1.json", std::ifstream::binary);

	Json::Value root;   // will contains the root value after parsing.
	bool parsingSuccessful = reader.parse(st, root, false);
	if (!parsingSuccessful)
	{
		// report to the user the failure and their locations in the document.
		std::cout << reader.getFormattedErrorMessages() << "\n";
	}


	//Tile 0 is een blanco;
	//Meerdere tilesets verhooght het nummer dus als tileset 1 192 tiles heeft gaat die op 2 verder met 193;

	//Eerst ophalen van de hoogte van tilecount
		//"height":10,	 "width":6,  "tilewidth":32,
	sf::Texture image;





	int tilesize = root["tilewidth"].asInt();
	int levelheight = root["height"].asInt();
	int levelwidht = root["width"].asInt();


	sf::IntRect subRect;
	subRect.width = tilesize;
	subRect.height = tilesize;

	/*Probeer maar variable te krijgen*/
	tileSets tileset[2];
	tile tegel[2][10][10];

	for (Json::Value::iterator it = root["tilesets"].begin(); it != root["tilesets"].end(); ++it)
	{
		Json::Value value = (*it);
		tileset[it.key().asInt()].firstgrid = value["firstgid"].asInt();
		tileset[it.key().asInt()].imageheight = value["imageheight"].asInt();
		tileset[it.key().asInt()].imagewidth = value["imagewidth"].asInt();
		tileset[it.key().asInt()].tilecounts = value["tilecount"].asInt();
		tileset[it.key().asInt()].tilesize = value["tilewidth"].asInt();
		tileset[it.key().asInt()].tileImage.loadFromFile(value["image"].asString());
	}



	for (Json::Value::iterator it = root["layers"].begin(); it != root["layers"].end(); ++it)
	{
		Json::Value value = (*it);

		const Json::Value array = value["data"];

		//Moet variable worden;
		int temp_array[10][6];

		int indentifier = 0;
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

				for (int tileIndex = 0; tileIndex < (sizeof(tileset) / sizeof(*tileset)); tileIndex++)
				{
					
					if (temp_int >= tileset[tileIndex].firstgrid && temp_int <=( tileset[tileIndex].firstgrid + tileset[tileIndex].tilecounts))
					{
						tileSetIndex = tileIndex;
						tileStartIndex = tileset[tileIndex].firstgrid;
						break;
					}
				}


				tileStartIndex -= 1;
				int widht_tileCount = tileset[tileSetIndex].imagewidth / tileset[tileSetIndex].tilesize;


			
				if (temp_int == 0) continue;


				int topindex = (temp_int - tileStartIndex) / (widht_tileCount );
				int leftindex = (temp_int-tileStartIndex) - (widht_tileCount * topindex);

				tegel[it.key().asInt()][i][j].sprite = sf::Sprite(tileset[tileSetIndex].tileImage);
				subRect.left = (leftindex - 1) * tilesize;
				subRect.top = topindex * tilesize;

				tegel[it.key().asInt()][i][j].sprite.setTextureRect(subRect);
				tegel[it.key().asInt()][i][j].sprite.setPosition(j*tilesize, i*tilesize);
			}


	}
	sf::RenderWindow window(sf::VideoMode(640, 480), "Team Echo!");

	while (window.isOpen())
	{

		window.clear();
		for (int a = 0; a < 2; a++)
		for (int i = 0; i < levelheight; ++i) {
			for (int j = 0; j < levelwidht; ++j) {
				window.draw(tegel[a][i][j].sprite);
			}
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}



		window.display();


	}
}


LevelImporter::~LevelImporter()
{
}
#undef JSON_DLL