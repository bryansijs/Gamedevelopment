#pragma once

#include <iostream>
#include <vector>
#include <map>

#include <SFML\System\Vector2.hpp>

class GameObject;
class Tile;

class MoveAction
{
public:
	MoveAction();
	~MoveAction();

	void Move(std::vector<std::string> directions, GameObject *gameObject, std::vector<Tile*>* tiles);
	void Move(std::vector<std::string> directions, GameObject *gameObject);
	void AnimateMovement(GameObject *gameObject, int state);

	void SetAnimationStates(int states);
	int animateState = 1;
private:
	void Move();

	GameObject *gameObject;
	std::vector<std::string> directions;
	std::vector<Tile*>* tiles;

	sf::Vector2f velocity;
	float speed = 150.0f;

	float animationDelay;
	int animationStates;
	void AnimateMovement(GameObject *gameObject);
};