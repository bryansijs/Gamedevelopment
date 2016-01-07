#pragma once

#include <iostream>
#include <Box2D/Box2D.h>

class DrawContainer;
class MoveContainer;
class GameObjectContainer;
class Player;
class GameContext;

class ShootAction
{
public:
	ShootAction();
	~ShootAction();

	void Shoot(DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world, Player* player, std::string direction, GameContext* gameContext);
private:
	float nextShot;
};

