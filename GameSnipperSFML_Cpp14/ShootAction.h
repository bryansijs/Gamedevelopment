#pragma once

#include <iostream>

class DrawContainer;
class MoveContainer;
class Player;

class ShootAction
{
public:
	ShootAction();
	~ShootAction();

	void Shoot(DrawContainer* drawContainer, MoveContainer* moveContainer, Player* player, std::string direction);
private:
	float shotRate = 0.5f;
	float nextShot;
};

