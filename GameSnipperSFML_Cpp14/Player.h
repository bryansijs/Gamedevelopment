#pragma once
#include "Unit.h"

class MoveContainer;
class DrawContainer;

class Player : public Unit
{
private:
	int keyAmount = 0;

public:
	Player(MoveContainer* moveContainer, DrawContainer* drawContainer);
	Player(MoveContainer* moveContainer, DrawContainer* drawContainer, GameObjectContainer *useContainer);
	Player();
	~Player();

	void AddKey(){keyAmount++;}
	void removeKey(){keyAmount--;}

	int getKey() { return keyAmount; }
};

