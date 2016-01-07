#pragma once

#include <map>
#include <iostream>

class KeyMappingExporter
{
public:
	KeyMappingExporter();
	~KeyMappingExporter();

	static void SaveToFile(std::string data);
	static std::string MappingToString(std::multimap<std::string, std::string> mapping);
};

