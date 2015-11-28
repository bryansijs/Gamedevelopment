#pragma once
#include "BaseInput.h"

class GameContext;

class PlayerInput : public BaseInput
{
public:
	PlayerInput(GameContext* gContext);
	void ProcessKeyActions() override;
private:
	GameContext* gContext;
	std::vector<std::string> moveDirections;
	void DoMovement();
};