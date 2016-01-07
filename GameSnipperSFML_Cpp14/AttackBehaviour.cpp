#include "stdafx.h"
#include "AttackBehaviour.h"
#include "MoveAction.h"
#include "Time.h"
#include "BaseEnemy.h"
AttackBehaviour::AttackBehaviour(GameObject* gameObject)
{
	this->setGameObject(gameObject);

	moveAction = new MoveAction{ gameObject, 0.10f };



	std::vector<std::string> dir =
	{
		{ "move-up" },
		{ "move-down" },
		{ "move-left" },
		{ "move-right" },
	/*	{ "move-upright" },
		{ "move-downright" },
		{ "move-upleft" },
		{ "move-downleft" },*/
		{ "move-not" }
	};

	this->swapDirections(dir);
	dir.clear();

	this->addDirection("move-not");
}

AttackBehaviour::~AttackBehaviour()
{

}

void AttackBehaviour::Update(sf::Vector2f viewPortPosition)
{
	moveAction->Move(this->getDirection());
	//START BULLET HELL!


}
