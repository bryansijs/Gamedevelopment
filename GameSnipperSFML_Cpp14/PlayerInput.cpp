#include "stdafx.h"
#include "PlayerInput.h"
#include "Input.h"
#include "KeyMapping.h"

#include <iostream>
#include <map>
#include <functional>
#include <SFML/Graphics.hpp>

using namespace std;

PlayerInput::PlayerInput()
{
}

PlayerInput::~PlayerInput()
{
}

bool PlayerInput::MoveEvent()
{
	multimap<string, string> keyMapping = KeyMapping::GetMapping();
	multimap<string, string>::iterator it;

	for (it = keyMapping.begin(); it != keyMapping.end(); ++it)
	{
		if (it->first.find("move") != string::npos)
		{
			string key = it->second;
			if (Input::GetKeyDown(it->second))
			{
				return true;
			}
		}
	}

	return false;
}

