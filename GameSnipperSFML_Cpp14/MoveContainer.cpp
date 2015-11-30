#include "stdafx.h"
#include "MoveContainer.h"
#include "MoveBehaviour.h"

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
	std::vector<MoveBehaviour*>::iterator it;
	for (it = behaviours.begin(); it != behaviours.end(); it++)
	{
		if ((*it) == behaviour)
			break;
	}

	behaviours.erase(it);
}
