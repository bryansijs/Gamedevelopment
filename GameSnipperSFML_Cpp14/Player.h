#pragma once
#include "Unit.h"
#include "PlayerActions.h"

class MoveContainer;
class DrawContainer;

class Player : public Unit
{
public:
	Player(MoveContainer* moveContainer, DrawContainer* drawContainer);
	Player(MoveContainer* moveContainer, DrawContainer* drawContainer, GameObjectContainer *useContainer);
	Player();
	PlayerActions* GetActions() { return &actions; };
	~Player() override;
private:
	PlayerActions actions = PlayerActions(this);
};

