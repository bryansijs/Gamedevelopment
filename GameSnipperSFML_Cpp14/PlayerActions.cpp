#include "stdafx.h"
#include "PlayerActions.h"

#include <vector>
#include "Time.h"
#include "Player.h"
#include "GameObjectContainer.h"
#include "GameObject.h"
#include "Tile.h"
#include "KeyMapping.h"


PlayerActions::PlayerActions(Player* player)
{
	this->player = player;
}

PlayerActions::~PlayerActions()
{
}

void PlayerActions::ProcessActions()
{
	bool animate = false;

	map<string, void(PlayerActions::*)()>::iterator it;

	for (vector<int>::size_type i = 0; i != activeKeys.size(); i++) {

		string map = KeyMapping::GetMap(activeKeys[i]);

		for (it = actions.begin(); it != actions.end(); ++it)
		{
			if (map.find(it->first) != string::npos)
			{
				if (find(activeActions.begin(), activeActions.end(), it->second) == activeActions.end())
				{
					activeActions.push_back(it->second);
				}
			}
		}

		// stop animation
		if(it->first.find("move") != string::npos)
		{
			animate = true;
		}
		else
		{
			
		}
	}
	if(!animate)
	{
		StandStill();
	}
	ExecuteActions();
}

void PlayerActions::ExecuteActions()
{
	vector<void(PlayerActions::*)()>::iterator it;
	for (it = activeActions.begin(); it != activeActions.end(); ++it)
	{
		auto function = *it;
		(this->*function)();
	}
	activeKeys.clear();
}

void PlayerActions::SetContainers(DrawContainer *drawContainer, MoveContainer *moveContainer, std::vector<Tile*>* tiles)
{
	this->drawContainer = drawContainer;
	this->moveContainer = moveContainer;
	this->tiles = tiles;
}

void PlayerActions::Move()
{
	StandStillTimerReset();

	std::vector<std::string> directions;

	for (std::vector<int>::size_type i = 0; i != activeKeys.size(); i++) {
		std::string map = KeyMapping::GetMap(activeKeys[i]);

		if (map.find("move") != std::string::npos)
		{
			directions.push_back(map);
			direction = map;
		}
	}

	direction = directions.at(0);
	moveAction.Move(directions, player, tiles);
}

void PlayerActions::Shoot()
{
	StandStillTimerReset();
	shootAction.Shoot(drawContainer, moveContainer, player, direction);
}

void PlayerActions::Use()
{
	StandStillTimerReset();

	if (useDelay > 0)
	{
		useDelay -= Time::deltaTime;
		return;
	}
	//std::cout << b <<  std::endl;
	/*std::cout << "My current location x y " << player->getPosition().x << " " << player->getPosition().y << std::endl;*/

	float playery = this->player->getPosition().y;
	float playerx = this->player->getPosition().x;
	for (GameObject* object : this->player->getgameObjectContainer()->getObjects())
	{
		//Check zit ik wel bij dit object in de beurt?
		//zojah dan gaan zijn actie uitvoeren;
		//anders nope nope
		//Dit moet worden afgevangen doormiddel van is colliding en de juiste directe!
		//Als we op dezelfde y zitten met een 32 ~48 verschil;
		//Als we op dezelfde x zittten met en 32 ~48 verschil; 
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

void PlayerActions::StandStill()
{
	if (StandStillTimer > 0)
	{
		moveAction.AnimateMovement(player, 1);
		StandStillTimer = StandStillTimer - Time::deltaTime;
		return;
	}

	// todo: add text to text displayer
	cout << "Let's take a walk!\n";
	StandStillTimerReset();
}