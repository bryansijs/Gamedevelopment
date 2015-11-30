#include "stdafx.h"
#include "Player.h"

#include "MoveContainer.h"
#include "DrawContainer.h"
#include <Box2D/Box2D.h>

#include "NormalMoveBehaviour.h"
#include "PlayerDrawBehaviour.h"

Player::Player(MoveContainer* moveContainer, DrawContainer* drawContainer, b2World* world)
{
	this->setMoveContainer(moveContainer);
	this->setDrawContainer(drawContainer);

	this->SetMoveBehaviour( new NormalMoveBehaviour(this) );
	this->setDrawBehaviour( new PlayerDrawBehaviour(this, 10, "Player.png"));
	
	this->setSize(32, 32);

	//this->createBoxDynamic(*world);

	
	this->getDrawContainer()->AddBehaviour(getDrawBehaviour());
}


Player::Player(MoveContainer* moveContainer, DrawContainer* drawContainer, GameObjectContainer* useContainer, b2World* world)
{
	this->setMoveContainer(moveContainer);
	this->setDrawContainer(drawContainer);

	this->SetMoveBehaviour(new NormalMoveBehaviour(this));
	this->setDrawBehaviour(new PlayerDrawBehaviour(this, 10, "Player.png"));

	this->setSize(32, 32);

	//this->createBoxDynamic(*world);
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
}

