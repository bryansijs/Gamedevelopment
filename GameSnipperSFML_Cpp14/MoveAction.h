#pragma once

#include <iostream>
#include <vector>

class Player;
class Tile;

class MoveAction
{
public:
	~MoveAction();

	void Move(std::string direction, Player *player, std::vector<Tile>* tiles);
	void AnimateMovement(Player *player, int state);
private:

	float velocity = 1.0f;

	int animateState = 1;
	float animationDelay;
	void AnimateMovement(Player *player);
};