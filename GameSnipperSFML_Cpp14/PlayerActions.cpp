#include "stdafx.h"
#include "PlayerActions.h"

#include <vector>
#include "Time.h"
#include "Player.h"
#include "DrawBehaviour.h"
#include "GameObjectContainer.h"
#include "KeyMapping.h"
#include "GameObject.h"
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

	if (resetAnimation)
	{
		moveAction.AnimateMovement(player, 1);
		//force van player op 0 zetten.
		player->getBody()->SetLinearVelocity(b2Vec2(0,0));
	}

	if (Input::GetKeyUp(KeyMapping::GetKey("use")))
	{
		useAction = true;
	}

	activeActions.clear();
	resetAnimation = true;
}

void PlayerActions::Move()
{
	resetAnimation = false;
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

	if (useAction)
	{
		//int b = this->player->getgameObjectContainer()->getObjects().size();
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
					object->doAction(player);
				}
			}
		}
		useAction = false;

	}
}