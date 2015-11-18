#pragma once

#include <iostream>

class Unit;
class DrawContainer;
class MoveContainer;

class ShootAction
{
public:
	ShootAction();
	~ShootAction();

	void Shoot(DrawContainer* drawContainer, MoveContainer* moveContainer, Unit* unit, std::string direction);
private:
	float shotRate = 50.0f;
	float nextShot;
};

