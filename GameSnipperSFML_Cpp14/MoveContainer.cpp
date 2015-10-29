#include "stdafx.h"
#include "MoveContainer.h"
#include "MoveBehaviour.h"

MoveContainer::MoveContainer()
{
}

MoveContainer::~MoveContainer()
{
}

void MoveContainer::Update()
{
	for each(MoveBehaviour* behaviour in behaviours)
	{
		behaviour->Update();
	}
}

void MoveContainer::AddBehaviour(MoveBehaviour* behaviour)
{
	behaviours.push_back(behaviour);
}

void MoveContainer::RemoveBehaviour(MoveBehaviour* behaviour)
{

}
