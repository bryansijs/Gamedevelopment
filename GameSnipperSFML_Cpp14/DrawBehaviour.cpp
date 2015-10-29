#include "stdafx.h"
#include "DrawBehaviour.h"

#include <SFML\Graphics.hpp>

void DrawBehaviour::Draw(sf::RenderWindow *window)
{
	window->draw(getCurrentImage());
}

sf::Sprite DrawBehaviour::getCurrentImage()
{
	return this->unitImage;
}

GameObject* DrawBehaviour::getGameObject()
{
	return gameObject;
}