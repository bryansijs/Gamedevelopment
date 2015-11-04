#pragma once
#include <vector>

class MoveBehaviour;

class MoveContainer
{
public:
	MoveContainer();
	~MoveContainer();

	void Update();
	void AddBehaviour(MoveBehaviour* behaviour);
	void RemoveBehaviour(MoveBehaviour* behaviour);
private:
	std::vector<MoveBehaviour*> behaviours;
};

