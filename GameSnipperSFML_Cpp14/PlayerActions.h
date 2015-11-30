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

	void ProcessActions() override;


	float useDelay = 0;
	void SetContainers(DrawContainer *drawContainer, MoveContainer *moveContainer, std::vector<Tile*>* tiles);
	void SetTiles(std::vector<Tile*>* t) { tiles = t; };

	void Move();
	void Shoot();
	void Use();

	bool used = false;
private:
	void ExecuteActions() override;

	std::map<std::string, void(PlayerActions::*)()> actions = {
		{ "move", &PlayerActions::Move },
		{ "shoot", &PlayerActions::Shoot },
		{ "use", &PlayerActions::Use }
	};

	std::vector<void(PlayerActions::*)()> activeActions;

	std::string direction = "move-left";
	std::string currentMap;

	DrawContainer *drawContainer;
	MoveContainer *moveContainer;

	DrawBehaviour drawBehaviour;
	MoveBehaviour moveBehaviour;

	MoveAction moveAction;
	ShootAction shootAction;

	Player *player;
	std::vector<Tile*>* tiles;

	bool fired = false;
	bool useAction = true;

	void StandStillTimerReset() { StandStillTimer = 1000; };
	int StandStillTimer = 1000;
	void StandStill();
};