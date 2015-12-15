#pragma once

#include <vector>
#include <map>

#include "DrawBehaviour.h"
#include "MoveBehaviour.h"

#include "MoveAction.h"
#include "ShootAction.h"
#include "BaseInput.h"

class Player;
class MoveContainer;
class DrawContainer;
class Tile;

class PlayerActions : public BaseInput
{
public:
	PlayerActions(Player *player);
	~PlayerActions();

	void ProcessActions();

	float useDelay = 0;
	void SetContainers(DrawContainer *drawContainer, MoveContainer *moveContainer, GameObjectContainer *gameObjectContainer);
	void SetWorld(b2World* world);

	void Move();
	void Shoot();
	void Use();

	bool used = false;
	std::vector<void(PlayerActions::*)()> activeActions;
private:
	void ExecuteActions();

	std::map<std::string, void(PlayerActions::*)()> actions = {
		{ "move", &PlayerActions::Move },
		{ "shoot", &PlayerActions::Shoot },
		{ "use", &PlayerActions::Use }
	};

	std::string direction = "move-down";
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
	bool useAction = true;
	bool resetMove = true;

	int notificationSwitch = 0;
	void StandStillTimerReset() { if (1500 > StandStillTimer) { StandStillTimer = 1500; } };
	int StandStillTimer = 2000;
	void StandStill();
};
