#include "stdafx.h"
#include "PlayerActions.h"
#include "KeyMapping.h"

PlayerActions::PlayerActions(Player *activePlayer)
{
	player = activePlayer;
}

PlayerActions::~PlayerActions()
{
}

void PlayerActions::ProcessActions(std::vector<std::string> &newActiveKeys, float newDeltaTime)
{
	activeKeys = newActiveKeys;
	deltaTime = newDeltaTime;

	std::map<std::string, void(PlayerActions::*)()>::iterator it;

	for (std::vector<int>::size_type i = 0; i != activeKeys.size(); i++) {
		std::string map = KeyMapping::GetMap(activeKeys[i]);

		for (it = possibleActions.begin(); it != possibleActions.end(); ++it)
		{
			if (map.find(it->first) != std::string::npos)
			{
				currentMap = map;

				auto function = it->second;
				(this->*function)();
			}
		}
	}
}

void PlayerActions::Move()
{
	if (currentMap == "move-up")
	{
		player->positions.y += -1.0f * (deltaTime / 10000);
	}
	if (currentMap == "move-down")
	{
		player->positions.y += 1.0f * (deltaTime / 10000);
	}
	if (currentMap == "move-left")
	{
		player->positions.x += -1.0f * (deltaTime / 10000);
	}
	if (currentMap == "move-right")
	{
		player->positions.x += 1.0f * (deltaTime / 10000);
	}
}

void PlayerActions::Shoot()
{
	
}

void PlayerActions::Use()
{
	
}
