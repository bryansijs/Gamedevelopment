#pragma once

#include <iostream>

class Player;

class MoveAction
{
public:
	MoveAction();
	~MoveAction();

	void Move(std::string direction, Player *player);
private:
	Player *player;

	float velocity = 1.0f;
};