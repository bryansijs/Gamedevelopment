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
	void Move();
private:


	GameObject *gameObject;
	std::vector<std::string> directions;
	sf::Vector2f velocity;
	float speed = 200.0f;

	Animation* animation;
};