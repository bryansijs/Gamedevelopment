#pragma once

#include <vector>
#include <iostream>
#include <map>

#include "DrawBehaviour.h"
#include "MoveBehaviour.h"

#include "MoveAction.h"
#include "ShootAction.h"

class Player;
class MoveContainer;
class DrawContainer;

class PlayerActions
{
public:
	PlayerActions();
	~PlayerActions();

	void SetPlayer(Player *activePlayer);
	void SetContainers(DrawContainer *drawContainer, MoveContainer *moveContainer);
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
	std::string direction = "move-left";
	std::string currentMap;

	DrawContainer *drawContainer;
	MoveContainer *moveContainer;

	DrawBehaviour drawBehaviour;
	MoveBehaviour moveBehaviour;

	MoveAction moveAction;
	ShootAction shootAction;

	Player *player;

	bool fired = false;

};
