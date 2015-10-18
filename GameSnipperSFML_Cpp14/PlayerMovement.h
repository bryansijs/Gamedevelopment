#pragma once

#include <iostream>

#include "Player.h"

using namespace std;

class PlayerMovement
{
public:
	PlayerMovement();
	~PlayerMovement();

	void Move(float deltaTime, Player* player);
	void SetX(float x);
	void SetY(float y);
private:
	int x, y = 0;
};