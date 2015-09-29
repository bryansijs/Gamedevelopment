#include "stdafx.h"
#include "LevelImporter.h"
#include <json\json.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define JSON_DLL

using namespace std;
LevelImporter::LevelImporter()
{
	std::cout << "We are starting here: " << std::endl;
	Json::Reader reader;

	std::ifstream st("./Resources/levels/level1.json",std::ifstream::binary);

	Json::Value root;   // will contains the root value after parsing.
	bool parsingSuccessful = reader.parse(st, root, false);
	if (!parsingSuccessful)
	{
		// report to the user the failure and their locations in the document.
		std::cout << reader.getFormattedErrorMessages()		<< "\n";
	}
	std::string encoding = root.get("encoding", "UTF-8").asString();
	std::cout << encoding << "\n";


	//Tile 0 is een blanco;
	//Meerdere tilesets verhooght het nummer dus als tileset 1 192 tiles heeft gaat die op 2 verder met 193;

	//Eerst ophalen van de hoogte van tilecount
		//"height":10,	 "width":6,  "tilewidth":32,
	/*"layers":[
        {
         "data":[0, 0, 0, 0, 0, 0, 
		 0,  0, 0, 0, 0, 0, 
		 0, 20, 19, 20, 19, 0,
		 0, 36, 35, 36, 35, 0,
		 0, 20, 19, 20, 19, 0, 
		 0, 36, 35, 36, 35, 0, 
		 0, 20, 19, 20, 19, 0, 
		 0, 36, 35, 36, 35, 0,
		 0, 20, 19, 20, 19, 0,
		 0, 0, 2, 2, 0, 0],
         "height":10,
         "name":"Floor",
         "opacity":1,
         "type":"tilelayer",
         "visible":true,
         "width":6,
         "x":0,
         "y":0
        }, 
        {
         "data":[199, 199, 199, 199, 199, 199, 
		 199,  195, 195, 195, 196,	 199,
		 199, 0, 0, 0, 0, 199,
		 199, 0, 0, 0, 0, 199,
		 199, 0, 0, 0, 0, 199,
		 199, 0, 0, 0, 0, 199, 
		 199, 0, 0, 0, 0, 199, 
		 199, 0, 0, 0, 0, 199,
		 199, 0, 0, 0, 0, 199,
		 199, 199, 0, 0, 199, 199],
         "height":10,
         "name":"Walls",
         "opacity":1,
         "properties":
            {
             "collision":"true"
            },
         "type":"tilelayer",
         "visible":true,
         "width":6,
         "x":0,
         "y":0
        }],*/
	//Tileset:
//	"renderorder":"right-down",
	/*  "image":".\/Resources\/tiles\/Sci-Fi-Tiles_A1.png",    
		"tilecount":192,
		"tileheight":32,
		"tilewidth":32
		"imageheight":384,
		"imagewidth":512,
	*/

	cout << "List of members:" << endl;
		for (Json::Value::iterator it = root["layers"].begin(); it != root["layers"].end(); ++it)
		
		{
				Json::Value key = it.key();
				Json::Value value = (*it);
				cout << "Key: " << key.toStyledString();
				cout << "Value: " << value.toStyledString();
		}

		
	
}


LevelImporter::~LevelImporter()
{
}
#undef JSON_DLL