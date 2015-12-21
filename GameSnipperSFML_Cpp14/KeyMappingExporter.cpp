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

void KeyMappingExporter::SaveToFile(std::string data)
{
	std::ofstream file{ "./Resources/key-mapping.json", std::ofstream::out };
	file << data;
	file.close();
}

std::string KeyMappingExporter::MappingToString(std::multimap<std::string, std::string> mapping)
{
	std::string output = "{\"mapping\":[";

	std::multimap<std::string, std::string>::iterator it;
	int i = 1;

	for (it = mapping.begin(); it != mapping.end(); ++it)
	{
		std::string map = it->first;
		std::string key = it->second;
		output.append("{\"map\": \"" + it->first + "\",\"key\": \"" + it->second + "\"}");

		if (i < mapping.size())
		{
			output.append(",");
		}

		i++;
	}

	output.append("]}");

	return output;
}
