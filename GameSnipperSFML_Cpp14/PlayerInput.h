#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class PlayerInput
{
public:
	PlayerInput();
	~PlayerInput();

	bool MoveEvent();
};

