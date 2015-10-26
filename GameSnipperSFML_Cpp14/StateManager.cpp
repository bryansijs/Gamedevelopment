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

void StateManager::PopState()
{
	if(!states.empty())
	{
		states.pop();
	}
}

void StateManager::RunState()
{
	if(!states.empty())
	{
		states.front()->Run();
	}
}

StateManager::StateManager()
{
}


StateManager::~StateManager()
{
}
