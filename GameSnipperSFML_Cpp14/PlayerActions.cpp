#include "stdafx.h"
#include "PlayerActions.h"

#include <vector>
#include "Time.h"
#include "Player.h"
#include "DrawBehaviour.h"
#include "GameObjectContainer.h"
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

void PlayerActions::SetContainers(DrawContainer *drawContainer, MoveContainer *moveContainer, std::vector<Tile*>* tiles)
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
	if (useDelay > 0)
	{
		useDelay -= Time::deltaTime;
		return;
	}

	int b = this->player->getgameObjectContainer()->getObjects().size();
	/*std::cout << "My current location x y " << player->getPosition().x << " " << player->getPosition().y << std::endl;*/

	float playery = this->player->getPosition().y;
	float playerx = this->player->getPosition().x;
	for (GameObject* object : this->player->getgameObjectContainer()->getObjects())
	{
		//Check zit ik wel bij dit object in de beurt?
		//zojah dan gaan zijn actie uitvoeren;
		//anders nope nope
		//Dit moet worden afgevangen doormiddel van is colliding en de juiste directe!
		//Als we op dezelfde y zitten met een 32 verschil;
		//Als we op dezelfde x zittten met en 32 verschil; 
		if (playery + 32 > object->getPosition().y && playery - 48 < object->getPosition().y)
		{
			if (playerx + 32 > object->getPosition().x && playerx - 48 < object->getPosition().x)
			{
				object->doAction();
			}
		}
	}

	useDelay = 7;
}