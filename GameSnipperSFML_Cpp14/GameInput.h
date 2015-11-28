#pragma once
#include "BaseInput.h"

class GameContext;

class GameInput : public BaseInput
{
public:
	GameInput(GameContext* gContext);
	void ProcessKeyActions() override;
private:
	GameContext* gContext;
};