#pragma once

#include <iostream>
#include <vector>

class Unit;
class Player;
class Tile;

class MoveAction
{
public:
	~MoveAction();

	void Move(std::string direction, Unit* unit, std::vector<Tile>* tiles);
	void AnimateMovement(Unit *unit, int state);
private:

	float velocity = 1.0f;

	int animateState = 1;
	float animationDelay;
	void AnimateMovement(Unit *player);
};