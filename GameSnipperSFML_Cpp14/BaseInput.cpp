#include "stdafx.h"
#include "BaseInput.h"
#include "Input.h"
#include "KeyMapping.h"
#include <map>
#include <SFML/Graphics.hpp>
#include "KeyMappingImporter.h"

BaseInput::BaseInput()
{
	KeyMappingImporter keyMappingImporter;
	keyMappingImporter.Import("./Resources/key-mapping.json");
	KeyMapping::ReloadMapping(keyMappingImporter.GetMapping());
}

BaseInput::~BaseInput()
{
	delete &activeKeys;
}

void BaseInput::CatchInput()
{
	multimap<string, string> mapping = KeyMapping::GetMapping();
	multimap<string, string>::iterator iterator;

	for (iterator = mapping.begin(); iterator != mapping.end(); ++iterator)
	{
		string key = iterator->second;

		if (Input::GetKeyDown(key))
		{
			AddActiveKey(key);
		}

		if (Input::GetKeyUp(key))
		{
			RemoveActiveKey(key);
		}
	}
}

void BaseInput::AddActiveKey(string key)
{
	if (find(activeKeys.begin(), activeKeys.end(), key) == activeKeys.end())
	{
		activeKeys.push_back(key);
	}
}

void BaseInput::RemoveActiveKey(string key)
{
	activeKeys.erase(remove(activeKeys.begin(), activeKeys.end(), key));
}