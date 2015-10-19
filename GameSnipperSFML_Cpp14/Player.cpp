#include "stdafx.h"
#include "Player.h"
#include "NormalMoveBehaviour.h"
#include "NormalDrawBehaviour.h"


//Player::Player(std::vector<MoveBehaviour*>* moves, std::vector<DrawBehaviour*>* draws, std::vector<Unit*>* units)
Player::Player()
{
	this->setPosition(400.0f, 400.0f);
	//this->allMoveBehaviours = moves;
	//this->allDrawBehaviours = draws;
	//this->allUnits = units;

	this->moveBehaviour = { new NormalMoveBehaviour(this) };
	this->drawBehaviour = { new NormalDrawBehaviour(this, 10, "Player.png") };

	//this->allMoveBehaviours->push_back(this->moveBehaviour);
	//this->allDrawBehaviours->push_back(this->drawBehaviour);
	//this->allUnits->push_back(this);
}

//Player::Player()
//{
//
//}

Player::~Player()
{
}

