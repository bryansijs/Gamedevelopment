#pragma once
#include <vector>
#include <queue>
class BaseState;

class StateManager
{
	//std::vector<BaseState*> states;
	std::queue<BaseState*> states;
public:
	void AddState(BaseState* state);
	void RemoveState(BaseState state);
	//void TerminateState(BaseState state);
	void PopState();
	void RunState();
	
	StateManager();
	~StateManager();
};

