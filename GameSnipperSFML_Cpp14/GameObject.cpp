#include "stdafx.h"
#include "GameObject.h"

#include "DrawContainer.h"
#include "MoveContainer.h"
#include "GameObjectContainer.h"

#include "NormalDrawBehaviour.h"
#include "WanderMoveBehaviour.h"
#include "MoveBehaviour.h"

#include "Tile.h"

GameObject::GameObject(DrawContainer *drawContainer, std::string textureUrl)
{
	this->drawContainer = drawContainer;
	this->drawBehaviour = { new NormalDrawBehaviour(this, 10, "./Resources/sprites/" + textureUrl) };
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

GameObject::GameObject(GameObjectContainer *gameObjectContainer, MoveContainer *moveContainer, std::string textureUrl)
{
	this->gameObjectContainer = gameObjectContainer;
	this->gameObjectContainer->AddObject(this);

	this->moveContainer = moveContainer;
	this->moveBehaviour = { new WanderMoveBehaviour(this) };
	this->moveContainer->AddBehaviour(this->moveBehaviour);
}

GameObject::GameObject(DrawContainer *drawContainer, GameObjectContainer *gameObjectContainer, MoveContainer *moveContainer, std::string textureUrl)
{
	this->drawContainer = drawContainer;
	this->moveContainer = moveContainer;

	this->drawBehaviour = { new NormalDrawBehaviour(this, 10, "./Resources/sprites/" + textureUrl) };
	this->moveBehaviour = { new WanderMoveBehaviour(this) };

	this->drawContainer->AddBehaviour(this->drawBehaviour);
	this->moveContainer->AddBehaviour(this->moveBehaviour);

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
	//drawContainer->RemoveBehaviour(this->drawBehaviour);
	this->drawBehaviour = newDrawBehaviour;
	//drawContainer->AddBehaviour(this->drawBehaviour);
}

void GameObject::SetMoveBehaviour(MoveBehaviour* moveBehaviour)
{
	//moveContainer->RemoveBehaviour(this->moveBehaviour);
	this->moveBehaviour = moveBehaviour;
	//moveContainer->AddBehaviour(this->moveBehaviour);
}

void GameObject::doAction()
{

}

void GameObject::doAction(Player* player)
{

}

bool GameObject::isColliding(std::vector<Tile*> tiles, sf::Vector2f velocity)
{

	std::vector<GameObject*>::iterator it;
	std::vector<GameObject*> temp = gameObjectContainer->getObjects();

	for (it = temp.begin(); it != temp.end(); it++) {
		if ((*it) != this && (*it)->isCollidable)
		{
			if (position.x + velocity.x < ((*it)->position.x + (*it)->getHeight()) &&
				(position.x + velocity.x + this->height) >(*it)->position.x )
				if (position.y + velocity.y < ((*it)->position.y + (*it)->getWidth()) &&
					(position.y + velocity.y + this->width) >(*it)->position.y) {
						return true;
			}
		}
	}

	for (int i = 0; i < tiles.size(); i++) {

		if (tiles.at(i)->isCollidable) {
			if (position.x + velocity.x < (tiles.at(i)->x_Position + 32) &&
				(position.x + velocity.x + 32) > tiles.at(i)->x_Position &&
				position.y + velocity.y < (tiles.at(i)->y_Position + 32) &&
				(position.y + velocity.y + 32) > tiles.at(i)->y_Position) {
				return true;
			}
		}
	}

	return false;
}
