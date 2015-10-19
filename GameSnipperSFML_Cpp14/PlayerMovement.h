#pragma once

#include <iostream>
#include <vector>

#include "Player.h"

class PlayerMovement
{
public:
	PlayerMovement(Player* player);
	~PlayerMovement();

	void Move(float deltaTime);
	void SetActiveKeys(std::vector<std::string> keys);
private:
	void SetPosition(float deltaTime, std::string direction);
	std::vector<std::string> activeKeys;
	Player* player;
};