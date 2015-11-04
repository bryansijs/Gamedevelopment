#pragma once

#include <iostream>
#include <map>
#include <fstream>

#include "Input.h"
#include <json\json.h>

using namespace std;

class KeyMappingImporter
{
public:
	KeyMappingImporter();
	~KeyMappingImporter();

	void Import(string json);
	multimap<string, string> GetMapping();
private:
	void GenerateMapping(Json::Value json);
	pair<string, string> CreateMap(string map, string key);

	multimap<string, string> mapping;
};

