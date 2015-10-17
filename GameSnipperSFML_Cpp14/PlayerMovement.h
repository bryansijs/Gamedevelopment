#pragma once

#include <iostream>

using namespace std;

class PlayerMovement
{
public:
	PlayerMovement();
	~PlayerMovement();

	void Move(float deltaTime);
	void SetX(float x);
	void SetY(float y);
private:
	int x, y = 0;
};