#include "stdafx.h"
#include "PlayerActions.h"

#include <vector>

#include "Player.h"
#include "DrawBehaviour.h"
#include "KeyMapping.h"
#include "GameObject.h"
#include "Tile.h"

PlayerActions::PlayerActions()
{
	
}

PlayerActions::~PlayerActions()
{
}

void PlayerActions::SetPlayer(Player *player)
{
	this->player = player;
}

void PlayerActions::SetContainers(DrawContainer *drawContainer, MoveContainer *moveContainer, std::vector<Tile>* tiles)
{
	this->drawContainer = drawContainer;
	this->moveContainer = moveContainer;
	this->tiles = tiles;
}

void PlayerActions::ProcessActions(std::vector<std::string> &newActiveKeys)
{
	activeKeys = newActiveKeys;

	std::map<std::string, void(PlayerActions::*)()>::iterator it;

	for (std::vector<int>::size_type i = 0; i != activeKeys.size(); i++) {
		std::string map = KeyMapping::GetMap(activeKeys[i]);

		for (it = actions.begin(); it != actions.end(); ++it)
		{
			if (map.find(it->first) != std::string::npos)
			{
				if (std::find(activeActions.begin(), activeActions.end(), it->second) == activeActions.end())
				{
					activeActions.push_back(it->second);
				}
			}
		}
	}

	ExecuteActions();
}

void PlayerActions::ExecuteActions()
{
	std::vector<void(PlayerActions::*)()>::iterator it;

	for (it = activeActions.begin(); it != activeActions.end(); ++it)
	{
		auto function = *it;
		(this->*function)();
	}

	activeActions.clear();
}

void PlayerActions::Move()
{
	std::vector<std::string> directions;

	for (std::vector<int>::size_type i = 0; i != activeKeys.size(); i++) {
		std::string map = KeyMapping::GetMap(activeKeys[i]);

		if (map.find("move") != std::string::npos)
		{
			directions.push_back(map);
			direction = map;
		}
	}

	moveAction.Move(directions, player, tiles);
}

void PlayerActions::Shoot()
{
	shootAction.Shoot(drawContainer, moveContainer, player, direction);
}

void PlayerActions::Use()
{
	
}