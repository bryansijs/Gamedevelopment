#include "stdafx.h"
#include "PlayerInput.h"
#include "PlayerMovement.h"
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

bool PlayerInput::MoveEvent()
{
	multimap<string, string> keyMapping = KeyMapping::GetMapping();
	multimap<string, string>::iterator it;

	for (it = keyMapping.begin(); it != keyMapping.end(); ++it)
	{
		string map = it->first;
		if (map.find("move-") != string::npos)
		{
			if (Input::GetKeyDown(it->second))
			{
				return true;
			}
		}
	}

	return false;
}

