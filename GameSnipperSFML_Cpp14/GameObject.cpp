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

bool GameObject::isColliding(std::vector<Tile> tiles, float newX, float newY)
{
	for (int i = 0; i < tiles.size(); i++) {

		if (tiles.at(i).isCollidable) {
			if (newX < (tiles.at(i).x_Position + 32) && (newX + 32) > tiles.at(i).x_Position && newY < (tiles.at(i).y_Position + 32) && (newY + 32) > tiles.at(i).y_Position) {
				//std::cout << "collide" << std::endl;
				return true;
			}
		}
	}
	return false;
}
