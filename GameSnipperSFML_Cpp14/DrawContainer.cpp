#include "stdafx.h"
#include "DrawContainer.h"
#include "DrawBehaviour.h"

DrawContainer::DrawContainer()
{
}

DrawContainer::~DrawContainer()
{
}

void DrawContainer::Draw(sf::RenderWindow *window)
{
	for each(DrawBehaviour *behaviour in behaviours)
	{
		behaviour->Draw(window);
	}
}

void DrawContainer::AddBehaviour(DrawBehaviour *behaviour)
{
	behaviours.push_back(behaviour);
}

void DrawContainer::RemoveBehaviour(DrawBehaviour *behaviour)
{

}