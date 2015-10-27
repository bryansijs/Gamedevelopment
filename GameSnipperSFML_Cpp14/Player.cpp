#include "stdafx.h"
#include "Player.h"

#include "MoveContainer.h"
#include "DrawContainer.h"

#include "NormalMoveBehaviour.h"
#include "PlayerDrawBehaviour.h"

Player::Player(MoveContainer* moveContainer, DrawContainer* drawContainer)
{
	this->moveContainer = moveContainer;
	this->drawContainer = drawContainer;

	this->moveBehaviour = { new NormalMoveBehaviour(this) };
	this->drawBehaviour = { new PlayerDrawBehaviour(this, 10, "Player.png") };

	this->drawContainer->AddBehaviour(drawBehaviour);
}

Player::Player()
{
	this->moveBehaviour = { new NormalMoveBehaviour(this) };
	this->drawBehaviour = { new PlayerDrawBehaviour(this, 10, "Player.png") };
}

Player::~Player()
{
}

