#pragma once

#include "input.h"

#include <map>
#include <iostream>

using namespace std;

class KeyMapping
{
public:
	KeyMapping();
	~KeyMapping();

	static void AddKeyMap(string map, string key);
	static void RemoveKeyMap(string map, string key);
	static void ReloadMapping(multimap<string, string> mapping);

	static string GetMap(string key);
	static string GetKey(string map);
	static void ChangeKey(string map, string key);
	static multimap<string, string> GetMapping();
private:
	static multimap<string, string> mapping;
};