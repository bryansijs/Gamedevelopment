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

		if (states.empty())
		{
			running = false;
		}
	}
}

void StateManager::PopState()
{
	if(!states.empty())
	{
		states.front()->Terminate();
		states.pop();
	}
}

void StateManager::RunState()
{
	running = true;

	while(running)
	{
		if (states.empty())
		{
			break;
		}

		states.front()->Update();
	}
}

StateManager::StateManager()
{
}


StateManager::~StateManager()
{
}
