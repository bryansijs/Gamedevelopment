#include "stdafx.h"
#include "ShootAction.h"

#include "Time.h"
#include "GameObject.h"
#include "DrawContainer.h"
#include "MoveContainer.h"
#include "ShotMoveBehaviour.h"
#include "Player.h"

ShootAction::ShootAction()
{
}

ShootAction::~ShootAction()
{
}
 
void ShootAction::Shoot(DrawContainer* drawContainer, MoveContainer* moveContainer, Player* player, std::string direction)
{
	if (Time::runningTime > nextShot)
	{
		nextShot = (float)Time::runningTime + (float)shotRate;

		GameObject* shot = new GameObject(drawContainer, "bullet.png");
		ShotMoveBehaviour* shotBehaviour = new ShotMoveBehaviour(shot);
		shotBehaviour->SetDirection(direction);
		moveContainer->AddBehaviour(shotBehaviour);

		shot->setPosition(sf::Vector2f(player->position.x, player->position.y));
		shot->setSize(16, 17);
		shot->set_Image_x(16);
		shot->set_Image_y(17);
	}
}