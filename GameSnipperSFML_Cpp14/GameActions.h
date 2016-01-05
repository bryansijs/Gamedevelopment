#pragma once

#include <map>
#include <vector>
#include "BaseInput.h"

class GameState;
class GameContext;

class GameActions : public BaseInput
{
public:
	GameActions(GameState* gamestate, GameContext* gameContext);
	~GameActions() override;

	void ProcessActions();
	void ExecuteActions();
private:
	GameState* gamestate;
	GameContext* gameContext;

	void NextLevel();
	void GodMode();

	std::vector<void(GameActions::*)()> activeActions;
	std::map<std::string, void(GameActions::*)()> actions = {
		{ "switch-up", &GameActions::NextLevel },
		{ "godmode", &GameActions::GodMode }
	};
};