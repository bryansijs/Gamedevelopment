#pragma once

#include "input.h"

#include <map>
#include <iostream>
#include <json\json.h>

class KeyMapping
{
public:
	KeyMapping();
	~KeyMapping();

	static void AddKeyMap(std::string map, std::string key);
	static void RemoveKeyMap(std::string map, std::string key);
	static void ReloadMapping(multimap<std::string, std::string> mapping);

	static std::string GetMap(std::string key);
	static std::string GetKey(std::string map);
	static void ChangeKey(std::string map, std::string key);
	static multimap<std::string, std::string> GetMapping();
private:
	static multimap<std::string, std::string> mapping;
};