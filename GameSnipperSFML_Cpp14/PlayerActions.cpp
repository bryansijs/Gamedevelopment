#include "stdafx.h"
#include "PlayerActions.h"

#include <vector>
#include "Time.h"
#include "Player.h"
#include "DrawBehaviour.h"
#include "GameObjectContainer.h"
#include "GameObject.h"
#include "Tile.h"

PlayerActions::PlayerActions(Player* player)
{
	this->player = player;
}

PlayerActions::~PlayerActions()
{
}

void PlayerActions::SetContainers(DrawContainer *drawContainer, MoveContainer *moveContainer, std::vector<Tile*>* tiles)
{
	this->drawContainer = drawContainer;
	this->moveContainer = moveContainer;
	this->tiles = tiles;
}

void PlayerActions::Move(std::vector<std::string>* moveDirections)
{
	direction = moveDirections->at(0);
	moveAction.Move(moveDirections, player, tiles);
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

void PlayerActions::DoNothing()
{
	moveAction.AnimateMovement(player, 1);
}