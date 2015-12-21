#include "stdafx.h"
#include "KeyMappingExporter.h"

#include <fstream>
#include <string>

KeyMappingExporter::KeyMappingExporter()
{
}

KeyMappingExporter::~KeyMappingExporter()
{
}

void KeyMappingExporter::SaveToFile(std::string location)
{
	std::ofstream output_file{ textfile, ios::app };
	output_file << "Deze kwam er later bij!\n";
}

void KeyMappingExporter::SaveToFile(std::string location, std::string filename)
{

}

std::string KeyMappingExporter::MappingToString(std::multimap<std::string, std::string> mapping)
{
	std::string output = "{\"mapping\":[";

	std::multimap<std::string, std::string>::iterator it;

	for (it = mapping.begin(); it != mapping.end(); ++it)
	{
		std::string map = it->first;
		std::string key = it->second;
		output.append("{\"map\": \"" + it->first + "\",\"key\": \"" + it->second + "\"},");
	}

	output.append("]}");

	return output;
}
