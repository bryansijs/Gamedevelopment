#include "stdafx.h"
#include "PlayerInput.h"
#include "Input.h"
#include "KeyMapping.h"

#include <map>
#include <functional>
#include <SFML/Graphics.hpp>


PlayerInput::PlayerInput()
{
}

PlayerInput::~PlayerInput()
{
}

void PlayerInput::CatchInput()
{
	multimap<string, string> mapping = KeyMapping::GetMapping();
	multimap<string, string>::iterator iterator;

	for (iterator = mapping.begin(); iterator != mapping.end(); ++iterator)
	{
		std::string key = iterator->second;

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

void PlayerInput::AddActiveKey(std::string key)
{
	if (std::find(activeKeys.begin(), activeKeys.end(), key) == activeKeys.end())
	{
		activeKeys.push_back(key);
	}
}

void PlayerInput::RemoveActiveKey(std::string key)
{
	activeKeys.erase(std::remove(activeKeys.begin(), activeKeys.end(), key));
}

std::vector<std::string> PlayerInput::GetActiveKeys()
{
	return activeKeys;
}
