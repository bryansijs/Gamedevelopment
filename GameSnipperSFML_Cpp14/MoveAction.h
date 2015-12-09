#pragma once

#include <iostream>
#include <vector>
#include <map>

#include <SFML\System\Vector2.hpp>

class GameObject;
class Tile;
class Animation;

class MoveAction
{
public:
	MoveAction(GameObject *gameObject, float delay);
	~MoveAction();

	void Move(std::vector<std::string> directions);
	void Reset();
private:
	void Move();

	GameObject *gameObject;
	std::vector<std::string> directions;
	sf::Vector2f velocity;
	float speed = 68.0f;

	Animation* animation;
};