#pragma once
#include "Unit.h"

class MoveContainer;
class DrawContainer;

class Player : public Unit
{
public:
	Player(MoveContainer* moveContainer, DrawContainer* drawContainer);
	Player();
	~Player();
};

