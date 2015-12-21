#include "stdafx.h"
#include "KeyMapping.h"

KeyMapping::KeyMapping()
{
}

KeyMapping::~KeyMapping()
{
}

multimap<std::string, std::string> KeyMapping::mapping;

void KeyMapping::AddKeyMap(std::string map, std::string key)
{
	mapping.insert(pair<std::string, std::string>(map, key));
}

void KeyMapping::RemoveKeyMap(std::string map, std::string key)
{
	multimap<std::string, std::string>::iterator it;

	for (it = mapping.begin(); it != mapping.end(); ++it)
	{
		if (it->first == map && it->second == key)
		{
			mapping.erase(it);
			return;
		}
	}
}

void KeyMapping::ReloadMapping(multimap<std::string, std::string> newMapping)
{
	mapping = newMapping;
}

std::string KeyMapping::GetMap(std::string key)
{
	multimap<std::string, std::string>::iterator it;

	for (it = mapping.begin(); it != mapping.end(); ++it)
	{
		if (it->second == key)
		{
			return it->first;
		}
	}
}

std::string KeyMapping::GetKey(std::string map)
{
	multimap<std::string, std::string>::iterator it;

	for (it = mapping.begin(); it != mapping.end(); ++it)
	{
		if (it->first == map)
		{
			return it->second;
		}
	}
}

void KeyMapping::ChangeKey(std::string map, std::string key)
{
	multimap<std::string, std::string>::iterator it;

	for (it = mapping.begin(); it != mapping.end(); ++it)
	{
		if (it->first == map)
		{
			it->second = key;
			return;
		}
	}
}

multimap<std::string, std::string> KeyMapping::GetMapping()
{
	return mapping;
}
