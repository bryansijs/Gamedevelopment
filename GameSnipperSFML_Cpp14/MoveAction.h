#pragma once

#include <iostream>
#include <vector>
#include <map>

#include <SFML\System\Vector2.hpp>

class Player;
class Tile;

class MoveAction
{
public:
	MoveAction();
	~MoveAction();


	void Move(std::vector<std::string> activeKeys, Player *player, std::vector<Tile*>* tiles);
	void AnimateMovement(Player *player, int state);

	int animateState = 1;
private:
	Player *player;
	sf::Vector2f velocity;
	float speed = 150.0f;

	float animationDelay;
	void AnimateMovement(Player *player);
};