#pragma once
#include "Unit.h"

class MoveContainer;
class DrawContainer;

class Player : public Unit
{
public:
	Player(MoveContainer* moveContainer, DrawContainer* drawContainer, b2World* world);
	Player(MoveContainer* moveContainer, DrawContainer* drawContainer, GameObjectContainer *useContainer, b2World* world);
	Player();
	~Player();
};

