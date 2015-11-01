#pragma once

#include <iostream>
#include <vector>

class Player;
class Tile;

class MoveAction
{
public:
	MoveAction();
	~MoveAction();

	void Move(std::string direction, Player *player, std::vector<Tile>* tiles);
private:
	Player *player;

	float velocity = 1.0f;
};