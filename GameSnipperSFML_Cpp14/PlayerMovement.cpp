#include "stdafx.h"
#include "PlayerMovement.h"
#include "KeyMapping.h"
#include "Input.h"

#include <algorithm>

PlayerMovement::PlayerMovement()
{
}

PlayerMovement::~PlayerMovement()
{
	delete(player);
}

void PlayerMovement::SetPlayer(Player * activePlayer)
{
	player = activePlayer;
}

void PlayerMovement::Move(float deltaTime)
{
	for (std::vector<int>::size_type i = 0; i != activeKeys.size(); i++) {
		std::string map = KeyMapping::GetMap(activeKeys[i]);

		if (map.find("move-") != std::string::npos)
		{
			SetPosition(deltaTime, map);
		}
	}
}

void PlayerMovement::SetPosition(float deltaTime, std::string direction)
{
	//TODO wat er word hier per direct iets aangepast?
	//position van het object word een private die je later kunt opvragenmet een getter
	//Daarna zul je deze moeten zetten door middel van een setter!
	if (direction == "move-up")
	{
		player->position.y += -1.0f * (deltaTime / 10000);
	}
	if (direction == "move-down")
	{
		player->position.y += 1.0f * (deltaTime / 10000);
	}
	if (direction == "move-left")
	{
		player->position.x += -1.0f * (deltaTime / 10000);
	}
	if (direction == "move-right")
	{
		player->position.x += 1.0f * (deltaTime / 10000);
	}
}

void PlayerMovement::SetActiveKeys(std::vector<std::string> keys)
{
	activeKeys = keys;
}
