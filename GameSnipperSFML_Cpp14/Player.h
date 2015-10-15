#pragma once
#include "Unit.h"

class Player : public Unit
{
public:
	Player(std::vector<MoveBehaviour*>* moves, std::vector<DrawBehaviour*>* draws, std::vector<Unit*>* units);
	Player();
	~Player();
};

