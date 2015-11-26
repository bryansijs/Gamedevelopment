#include "stdafx.h"
#include "Player.h"

#include "MoveContainer.h"
#include "DrawContainer.h"

#include "NormalMoveBehaviour.h"
#include "PlayerDrawBehaviour.h"

Player::Player(MoveContainer* moveContainer, DrawContainer* drawContainer)
{
	this->setMoveContainer(moveContainer);
	this->setDrawContainer(drawContainer);

	this->SetMoveBehaviour( new NormalMoveBehaviour(this) );
	this->setDrawBehaviour( new PlayerDrawBehaviour(this, 10, "Player.png"));

	this->setSize(32, 32);

	this->getDrawContainer()->AddBehaviour(getDrawBehaviour());
}


Player::Player(MoveContainer* moveContainer, DrawContainer* drawContainer, GameObjectContainer* useContainer)
{
	this->setMoveContainer(moveContainer);
	this->setDrawContainer(drawContainer);

	this->SetMoveBehaviour(new NormalMoveBehaviour(this));
	this->setDrawBehaviour(new PlayerDrawBehaviour(this, 10, "Player.png"));

	this->setSize(32, 32);

	this->getDrawContainer()->AddBehaviour(getDrawBehaviour());

	this->setUseContainer(useContainer);
}



Player::Player()
{
	this->SetMoveBehaviour ( new NormalMoveBehaviour(this) );
	this->setDrawBehaviour(new PlayerDrawBehaviour(this, 10, "Player.png"));
}

Player::~Player()
{
	delete &actions;
}

