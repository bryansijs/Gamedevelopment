#include "stdafx.h"
#include "KeyMapping.h"

KeyMapping::KeyMapping()
{
}

KeyMapping::~KeyMapping()
{
}

multimap<string, string> KeyMapping::mapping;

void KeyMapping::AddKeyMap(string map, string key)
{
	mapping.insert(pair<string, string>(map, key));
}

void KeyMapping::RemoveKeyMap(string map, string key)
{
	multimap<string, string>::iterator it;

	for (it = mapping.begin(); it != mapping.end(); ++it)
	{
		if (it->first == map && it->second == key)
		{
			mapping.erase(it);
			return;
		}
	}
}

void KeyMapping::ReloadMapping(multimap<string, string> newMapping)
{
	mapping = newMapping;
}

string KeyMapping::GetMap(string key)
{
	multimap<string, string>::iterator it;

	for (it = mapping.begin(); it != mapping.end(); ++it)
	{
		if (it->second == key)
		{
			return it->first;
		}
	}
}

string KeyMapping::GetKey(string map)
{
	multimap<string, string>::iterator it;

	for (it = mapping.begin(); it != mapping.end(); ++it)
	{
		if (it->first == map)
		{
			return it->second;
		}
	}
}

multimap<string, string> KeyMapping::GetMapping()
{
	return mapping;
}