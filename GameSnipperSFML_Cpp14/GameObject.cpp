#include "stdafx.h"
#include "GameObject.h"
#include "DrawContainer.h"
#include "UseContainer.h"
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


GameObject::GameObject(UseContainer *useContainer)
{
	this->useContainer = useContainer;
	this->useContainer->AddObject(this);
}

GameObject::GameObject(DrawContainer *drawContainer, UseContainer *useContainer,std::string textureUrl)
{
	this->drawContainer = drawContainer;
	this->drawBehaviour = { new NormalDrawBehaviour(this, 10, "./Resources/sprites/" + textureUrl) };
	this->drawContainer->AddBehaviour(this->drawBehaviour);
	this->useContainer = useContainer;
	this->useContainer->AddObject(this);
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
