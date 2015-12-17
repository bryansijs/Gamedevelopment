#include "stdafx.h"
#include "DrawContainer.h"
#include "DrawBehaviour.h"

DrawContainer::DrawContainer()
{
}

DrawContainer::~DrawContainer()
{
}

void DrawContainer::Draw(sf::RenderWindow *window, sf::Vector2f viewPortPosition)
{
	for each(DrawBehaviour *behaviour in behaviours)
	{
		behaviour->Draw(window,viewPortPosition);
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
