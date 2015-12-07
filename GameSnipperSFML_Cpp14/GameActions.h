#pragma once

#include <map>
#include <vector>
#include "BaseInput.h"

class GameState;

class GameActions : public BaseInput
{
public:
	GameActions(GameState* gamestate);
	~GameActions() override;

	void ProcessActions();
	void ExecuteActions();
private:
	GameState* gamestate;
	void NextLevel();
	void Test();
	std::vector<void(GameActions::*)()> activeActions;
	std::map<std::string, void(GameActions::*)()> actions = {
		{ "switch-up", &GameActions::NextLevel },
		{ "switch-down", &GameActions::Test }
	};
};