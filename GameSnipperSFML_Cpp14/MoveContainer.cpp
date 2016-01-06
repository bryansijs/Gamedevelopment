#include "stdafx.h"
#include "MoveContainer.h"
#include "MoveBehaviour.h"
#include "WanderMoveBehaviour.h"
MoveContainer::MoveContainer()
{
}

MoveContainer::~MoveContainer()
{
}

void MoveContainer::Update(sf::Vector2f viewPortPosition)
{
	for each(MoveBehaviour* behaviour in behaviours)
	{
		behaviour->Update(viewPortPosition);
	}
}

void MoveContainer::AddBehaviour(MoveBehaviour* behaviour)
{
	behaviours.push_back(behaviour);
}

void MoveContainer::RemoveBehaviour(MoveBehaviour* behaviour)
{

	/*	for (int i = 0; i < behaviours.size(); i++)
	{
		if (behaviours.at(i) == behaviour)
		{
			//	behaviours.at(i) = nullptr;
			behaviours.erase(behaviours.begin() + i);
			break;
		}
	}*/
	std::vector<MoveBehaviour*>::iterator it;
	for (it = behaviours.begin(); it != behaviours.end(); it++)
	{
		if ((*it) == behaviour)
		{
			behaviours.erase(it);
			break;
		}
	}
}
