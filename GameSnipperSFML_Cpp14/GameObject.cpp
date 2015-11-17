#include "stdafx.h"
#include "GameObject.h"

#include "DrawContainer.h"
#include "NormalDrawBehaviour.h"
#include "MoveBehaviour.h"
#include "Tile.h"

//GameObject::GameObject(std::vector<DrawBehaviour*>* draws, std::string textureUrl)
GameObject::GameObject(DrawContainer *drawContainer, std::string textureUrl)
{
	this->drawContainer = drawContainer;
	this->drawBehaviour = { new NormalDrawBehaviour(this, 10, "./Resources/sprites/"+textureUrl) };
	this->drawContainer->AddBehaviour(this->drawBehaviour);
}

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	
}


void GameObject::setDrawBehaviour(DrawBehaviour* newDrawBehaviour)
{
	this->drawBehaviour = newDrawBehaviour;
}

void GameObject::SetMoveBehaviour(MoveBehaviour* moveBehaviour)
{
	this->moveBehaviour = moveBehaviour;
}

bool GameObject::isColliding(std::vector<Tile> tiles, sf::Vector2f velocity)
{
	for (int i = 0; i < tiles.size(); i++) {

		if (tiles.at(i).isCollidable) {
			if (position.x + velocity.x < (tiles.at(i).x_Position + 32) &&
				(position.x + velocity.x + 32) > tiles.at(i).x_Position &&
				position.y + velocity.y < (tiles.at(i).y_Position + 32) &&
				(position.y + velocity.y + 32) > tiles.at(i).y_Position) {
				return true;
			}
		}
	}
	return false;
}
