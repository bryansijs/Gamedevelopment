#include "stdafx.h"
#include "GameObject.h"
#include "DrawContainer.h"
#include "GameObjectContainer.h"
#include "NormalDrawBehaviour.h"
#include "MoveBehaviour.h"
#include "Tile.h"


GameObject::GameObject(DrawContainer *drawContainer, std::string textureUrl)
{
	this->drawContainer = drawContainer;
	this->drawBehaviour = { new NormalDrawBehaviour(this, 10, "./Resources/sprites/"+textureUrl) };
	this->drawContainer->AddBehaviour(this->drawBehaviour);
}

GameObject::GameObject(DrawContainer *drawContainer)
{
	
}


GameObject::GameObject(GameObjectContainer *gameObjectContainer)
{
	this->gameObjectContainer = gameObjectContainer;
	this->gameObjectContainer->AddObject(this);
}

GameObject::GameObject(DrawContainer *drawContainer, GameObjectContainer *gameObjectContainer,std::string textureUrl)
{
	this->drawContainer = drawContainer;
	this->drawBehaviour = { new NormalDrawBehaviour(this, 10, "./Resources/sprites/" + textureUrl) };
	this->drawContainer->AddBehaviour(this->drawBehaviour);
	this->gameObjectContainer = gameObjectContainer;
	this->gameObjectContainer->AddObject(this);
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

void GameObject::setProperties(std::map<std::string, std::string>& properties)
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

void GameObject::doAction()
{

}
void GameObject::doAction(Player* player)
{

}

bool GameObject::isColliding(std::vector<Tile*> tiles, float newX, float newY)
{
	for (int i = 0; i < tiles.size(); i++) {

		if (tiles.at(i)->isCollidable) {
			if (newX < (tiles.at(i)->x_Position + 32) && (newX + 32) > tiles.at(i)->x_Position && newY < (tiles.at(i)->y_Position + 32) && (newY + 32) > tiles.at(i)->y_Position) {
				//std::cout << "collide" << std::endl;
				return true;
			}
		}
	}
	return false;
}
