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
class Tile;

class PlayerActions
{
public:
	PlayerActions(Player *player);
	~PlayerActions();
	float useDelay = 0;
	void SetContainers(DrawContainer *drawContainer, MoveContainer *moveContainer, GameObjectContainer *gameObjectContainer);
	void SetWorld(b2World* world);
	void ProcessActions(std::vector<std::string> &newActiveKeys);

	void Move();
	void Shoot();
	void Use();


	bool used = false;
private:
	void ExecuteActions();

	std::map<std::string, void(PlayerActions::*)()> actions = {
		{ "move", &PlayerActions::Move },
		{ "shoot", &PlayerActions::Shoot },
		{ "use", &PlayerActions::Use }
	};

	std::vector<void(PlayerActions::*)()> activeActions;

	std::vector<std::string> activeKeys;

	std::string direction = "move-left";
	std::string currentMap;

	DrawContainer *drawContainer;
	MoveContainer *moveContainer;
	GameObjectContainer * gameObjectContainer;

	DrawBehaviour drawBehaviour;
	MoveBehaviour moveBehaviour;

	MoveAction* moveAction;
	ShootAction shootAction;

	Player *player;
	b2World* world;

	bool fired = false;
	bool resetMove = true;
	bool useAction = true;
};

