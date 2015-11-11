#pragma once
#include <vector>
#include <queue>
class BaseState;

class StateManager
{
private:
	std::queue<BaseState*> states;

	bool running = false;
public:
	void AddState(BaseState* state);
	void RemoveState(BaseState state);
	void StartNextState();
	void PopState();
	void RunState();
	
	StateManager();
	~StateManager();
};

