#pragma once
#include <vector>

#include <SFML\System\Vector2.hpp>

class MoveBehaviour;

class MoveContainer
{
public:
	MoveContainer();
	~MoveContainer();

	void Update(sf::Vector2f);
	void AddBehaviour(MoveBehaviour* behaviour);
	void RemoveBehaviour(MoveBehaviour* behaviour);
private:
	std::vector<MoveBehaviour*> behaviours;
};

