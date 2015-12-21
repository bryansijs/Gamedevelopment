#pragma once

#include <map>
#include <iostream>

class KeyMappingExporter
{
public:
	KeyMappingExporter();
	~KeyMappingExporter();

	static void SaveToFile(std::string location);
	static void SaveToFile(std::string location, std::string filename);
	static std::string MappingToString(std::multimap<std::string, std::string> mapping);
};

