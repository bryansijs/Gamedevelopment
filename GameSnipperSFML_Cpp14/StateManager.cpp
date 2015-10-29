#include "stdafx.h"
#include "StateManager.h"
#include "BaseState.h"


void StateManager::AddState(BaseState* state)
{
	states.push(state);
}

void StateManager::RemoveState(BaseState state)
{
	
}

void StateManager::StartNextState()
{
	if (!states.empty())
	{
		states.front()->Terminate();
		states.pop();
		if (!states.empty())
		{
			RunState();
		}
	}
}

void StateManager::PopState()
{
	if(!states.empty())
	{
		states.pop();
	}
}

void StateManager::RunState()
{
	states.front()->Run();
}

StateManager::StateManager()
{
}


StateManager::~StateManager()
{
}
