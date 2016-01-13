#include "stdafx.h"
#include "KeyMappingImporter.h"
#define JSON_DLL

KeyMappingImporter::KeyMappingImporter()
{
}

KeyMappingImporter::~KeyMappingImporter()
{
}

void KeyMappingImporter::Import(string json)
{
	ifstream inputFileStream;
	inputFileStream.open(json);

	Json::Reader jsonReader;
	Json::Value jsonRoot;

	bool parsed = jsonReader.parse(inputFileStream, jsonRoot, false);

	if (parsed)
	{
		GenerateMapping(jsonRoot);

		inputFileStream.clear();
		inputFileStream.close();
		return;
	}

	inputFileStream.clear();
	inputFileStream.close();

	throw("Json could not be parsed.");
}

multimap<string, string> KeyMappingImporter::GetMapping()
{
	return mapping;
}

void KeyMappingImporter::GenerateMapping(Json::Value json)
{
	for (Json::Value::iterator it = json["mapping"].begin(); it != json["mapping"].end(); ++it)
	{
		Json::Value value = (*it);
		mapping.insert(CreateMap(value["map"].asString(), value["key"].asString()));
	}
}

pair<string, string> KeyMappingImporter::CreateMap(string map, string key)
{
	return pair<string, string>(map, key);
}
