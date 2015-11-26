#pragma once

#include <vector>
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
	PlayerActions(Player* activePlayer);
	~PlayerActions();
	float useDelay; 
	void SetContainers(DrawContainer *drawContainer, MoveContainer *moveContainer, std::vector<Tile*>* tiles);
	void setTiles(std::vector<Tile*>* t) { tiles = t; };
	void Move(std::string direction);
	void Shoot();
	void Use();
private:
	std::string direction = "move-left";

	DrawContainer *drawContainer;
	MoveContainer *moveContainer;

	DrawBehaviour drawBehaviour;
	MoveBehaviour moveBehaviour;

	MoveAction moveAction;
	ShootAction shootAction;

	Player *player;
	std::vector<Tile*>* tiles;

	bool fired = false;

};

