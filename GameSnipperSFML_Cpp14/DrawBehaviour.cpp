#include "stdafx.h"
#include "DrawBehaviour.h"

#include <SFML\Graphics.hpp>

void DrawBehaviour::Draw(sf::RenderWindow *window, sf::Vector2f viewPortPosition)
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


bool DrawBehaviour::isVisible(int screenX, int screenY)
{
	return (gameObject->getPosition().x > screenX && gameObject->getPosition().x < screenX + 960 && gameObject->getPosition().y > screenY && gameObject->getPosition().y < screenY + 640);

}