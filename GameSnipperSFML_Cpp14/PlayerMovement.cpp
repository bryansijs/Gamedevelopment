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
		float temp = player->getPositionY()  + (-1.0f * (deltaTime / 10000));
		player->setPosition(sf::Vector2f(player->getPositionX(), temp));
	}
	if (direction == "move-down")
	{
		float temp = player->getPositionY() - (-1.0f * (deltaTime / 10000));
		player->setPosition(sf::Vector2f(player->getPositionX(), temp));
	}
	if (direction == "move-left")
	{

		float temp = player->getPositionX();
			temp += -1.0f * (deltaTime / 10000);
		player->setPosition(sf::Vector2f(temp,player->getPositionY() ));

		
	}
	if (direction == "move-right")
	{

		float temp = player->getPosition().x;
		temp -= 1.0f * (deltaTime / 10000);
		player->setPosition(sf::Vector2f(int(temp), player->getPositionY()));
	}
}

void PlayerMovement::SetActiveKeys(std::vector<std::string> keys)
{
	activeKeys = keys;
}
