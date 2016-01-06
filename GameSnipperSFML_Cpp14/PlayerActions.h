#pragma once

#include <vector>
#include <map>

#include "DrawBehaviour.h"
#include "MoveBehaviour.h"

#include "MoveAction.h"
#include "ShootAction.h"
#include "BaseInput.h"
#include "GameContext.h"

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

	void SetContext(GameContext* context);

	void Move();
	void Shoot();
	void Use();
	void Equip();

	bool used = false;
	std::vector<void(PlayerActions::*)()> activeActions;
private:
	void ExecuteActions();

	std::map<std::string, void(PlayerActions::*)()> actions = {
		{ "move", &PlayerActions::Move },
		{ "shoot", &PlayerActions::Shoot },
		{ "use", &PlayerActions::Use },
		{ "equip", &PlayerActions::Equip }
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
	GameContext* context;

	bool fired = false;
	bool useAction = true;
	bool resetMove = true;

	int notificationSwitch = 0;
	void StandStillTimerReset() { if (750 > StandStillTimer) { StandStillTimer = 750; } };
	int StandStillTimer = 1500;
	void StandStill();
};
