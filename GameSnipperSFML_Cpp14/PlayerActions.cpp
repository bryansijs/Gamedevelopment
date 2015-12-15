#include "stdafx.h"
#include "PlayerActions.h"

#include <vector>
#include "Player.h"
#include "DrawBehaviour.h"
#include "GameObjectContainer.h"
#include "KeyMapping.h"
#include "GameObject.h"

#include "Time.h"
#include "StorylineManager.h"


PlayerActions::PlayerActions(Player *player)
{
	this->player = player;
	moveAction = new MoveAction{ player, 0.10f };
}

PlayerActions::~PlayerActions()
{

}

void PlayerActions::SetContainers(DrawContainer *drawContainer, MoveContainer *moveContainer, GameObjectContainer *gameObjectContainer)
{
	this->drawContainer = drawContainer;
	this->moveContainer = moveContainer;
	this->gameObjectContainer = gameObjectContainer;
}

void PlayerActions::SetWorld(b2World * world)
{
	this->world = world;
}

void PlayerActions::ProcessActions()
{
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
	vector<void(PlayerActions::*)()>::iterator it;

	for (it = activeActions.begin(); it != activeActions.end(); ++it)
	{
		auto function = *it;
		(this->*function)();
	}


	if (resetMove)
	{
		moveAction->Reset();
	}
	
	if (Input::GetKeyUp(KeyMapping::GetKey("use")))
	{
		useAction = true;
	}

	if (Input::GetKeyDown("U"))
	{
		player->setHealth(0);
	}

	activeActions.clear();

	resetMove = true;
}

void PlayerActions::Move()
{
	StandStillTimerReset();

	resetMove = false;
	std::vector<std::string> directions;

	for (std::vector<int>::size_type i = 0; i != activeKeys.size(); i++) {
		std::string map = KeyMapping::GetMap(activeKeys[i]);

		if (map.find("move") != std::string::npos)
		{
			directions.push_back(map);
			direction = map;
		}
	}

	moveAction->Move(directions);
}

void PlayerActions::Shoot()
{
	StandStillTimerReset();
	shootAction.Shoot(drawContainer, moveContainer, gameObjectContainer, world, player, direction);
}


void PlayerActions::Use()
{
	StandStillTimerReset();

	if (useAction)
	{
		//int b = this->player->getgameObjectContainer()->getObjects().size();
		//std::cout << b <<  std::endl;
		/*std::cout << "My current location x y " << player->getPosition().x << " " << player->getPosition().y << std::endl;*/

		float playery = this->player->getBody()->GetPosition().y;
		float playerx = this->player->getBody()->GetPosition().x;

		for (GameObject* object : this->player->getgameObjectContainer()->getObjects())
		{
			//Check zit ik wel bij dit object in de beurt?
			//zojah dan gaan zijn actie uitvoeren;
			//anders nope nope
			//Dit moet worden afgevangen doormiddel van is colliding en de juiste directe!
			//Als we op dezelfde y zitten met een 32 ~48 verschil;
			//Als we op dezelfde x zittten met en 32 ~48 verschil; 

			float y = object->getPosition().y;
			float x = object->getPosition().x;
			if (playery + 48 > y && playery - 48 < y)
			{
				if (playerx + 48  >x && playerx - 48 <x)
				{
					object->doAction(player);
				}
			}
		}
		useAction = false;
	}
}

void PlayerActions::StandStill()
{
	player->getBody()->SetLinearVelocity(b2Vec2(0, 0));

	if (StandStillTimer > 0)
	{		
		StandStillTimer = StandStillTimer - Time::deltaTime;
		return;
	}

	switch (notificationSwitch)
	{
	case 0:
		StorylineManager::Add("What are you waiting for?");
		notificationSwitch++;
		break;
	case 1:
		StorylineManager::Add("I'm still waiting!");
		notificationSwitch++;
		break;
	case 2:
		StorylineManager::Add("I'm bored...");
		notificationSwitch = 0;
		break;
	}

	StandStillTimerReset();
}