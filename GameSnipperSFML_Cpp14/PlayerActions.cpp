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
	direction = currentMap;
	moveAction.Move(direction, player, tiles);
}

void PlayerActions::Shoot()
{
	shootAction.Shoot(drawContainer, moveContainer, player, direction);
}

void PlayerActions::Use()
{
	
}