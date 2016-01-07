#include "stdafx.h"
#include "DrawContainer.h"
#include "DrawBehaviour.h"
#include "GameObject.h"
#include <algorithm>

DrawContainer::DrawContainer()
{
	Discoverdids.push_back(0);
}

DrawContainer::~DrawContainer()
{
}

void DrawContainer::Draw(sf::RenderWindow *window, sf::Vector2f viewPortPosition)
{

	for each(DrawBehaviour *behaviour in behaviours)
	{
		if (std::find(Discoverdids.begin(), Discoverdids.end(), behaviour->getGameObject()->getVisibleId()) != Discoverdids.end()) {
			behaviour->Draw(window, viewPortPosition);
		}
	}
}

void DrawContainer::AddBehaviour(DrawBehaviour *behaviour)
{
	behaviours.push_back(behaviour);
}

void DrawContainer::RemoveBehaviour(DrawBehaviour *behaviour)
{
	std::vector<DrawBehaviour*>::iterator it; 
	for (it = behaviours.begin(); it != behaviours.end(); it++)
	{
		if ((*it) == behaviour)
		{
			behaviours.erase(it);
			break;
		}
	}
}

bool DrawContainer::checkIfidIsDiscoverd(int id)
{
	if (std::find(Discoverdids.begin(), Discoverdids.end(), id) != Discoverdids.end()) {
		return true;
	}

	return false;
}
