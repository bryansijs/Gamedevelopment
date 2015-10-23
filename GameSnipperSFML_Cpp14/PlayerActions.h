#pragma once

#include <vector>
#include <iostream>
#include <map>

#include "Player.h"

class PlayerActions
{
public:
	PlayerActions(Player *player);
	~PlayerActions();

	void ProcessActions(std::vector<std::string> &newActiveKeys);
	void Move();
	void Shoot();
	void Use();
private:
	std::map<std::string, void(PlayerActions::*)()> possibleActions = {
		{ "move", &PlayerActions::Move },
		{ "shoot", &PlayerActions::Shoot },
		{ "use", &PlayerActions::Use }
	};

	std::vector<std::string> activeKeys;
	std::string currentMap;

	Player *player;
};

