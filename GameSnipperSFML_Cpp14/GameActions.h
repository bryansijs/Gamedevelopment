#pragma once

#include <map>
#include <vector>
#include "BaseInput.h"

class GameActions : public BaseInput
{
public:
	GameActions();
	~GameActions() override;

	void ProcessActions();
	void ExecuteActions();
private:
	std::vector<void(GameActions::*)()> activeActions;
	std::map<std::string, void(GameActions::*)()> actions = {};
};