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

GameObject::GameObject(DrawContainer *drawContainer, GameObjectContainer *gameObjectContainer, std::string textureUrl)
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

void GameObject::move()
{
	this->moveBehaviour->Update();
}


void GameObject::doAction()
{

}
void GameObject::doAction(Player* player)
{

}

bool GameObject::isColliding(std::vector<Tile*> tiles, sf::Vector2f velocity)
{
//<<<<<<< HEAD
//	//for (int i = 0; i < tiles.size(); i++) {
//
//	//	if (tiles.at(i)->isCollidable) {
//	//		if (getPosition() + velocity.x < (tiles.at(i)->x_Position + 28) &&
//	//			(getPosition().x + velocity.x + 28) > tiles.at(i)->x_Position &&
//	//			getPosition().y + velocity.y < (tiles.at(i)->y_Position + 12) &&
//	//			(getPosition().y + velocity.y + 32) > tiles.at(i)->y_Position) {
//	//			return true;
//	//		}
//	//	}
//	//}
//=======
//
//	std::vector<GameObject*>::iterator it;
//	std::vector<GameObject*> temp = gameObjectContainer->getObjects();
//
//	for (it = temp.begin(); it != temp.end(); it++) {
//		if ((*it) != this && (*it)->isCollidable)
//		{
//			if (position.x + velocity.x < ((*it)->position.x + (*it)->getHeight()) &&
//				(position.x + velocity.x + this->height) >(*it)->position.x )
//				if (position.y + velocity.y < ((*it)->position.y + (*it)->getWidth()) &&
//					(position.y + velocity.y + this->width) >(*it)->position.y) {
//						return true;
//			}
//		}
//	}
//
//
//
//	for (int i = 0; i < tiles.size(); i++) {
//
//		if (tiles.at(i)->isCollidable) {
//			if (position.x + velocity.x < (tiles.at(i)->x_Position + 32) &&
//				(position.x + velocity.x + 32) > tiles.at(i)->x_Position &&
//				position.y + velocity.y < (tiles.at(i)->y_Position + 32) &&
//				(position.y + velocity.y + 32) > tiles.at(i)->y_Position) {
//				return true;
//			}
//		}
//	}
//>>>>>>> 314fb8b385d524ad64d5e7a6f26bce464efad1dd
	return false;
}

void GameObject::createBoxStatic(b2World& World)
{	
	myBodyDef.type = b2_staticBody;

	Body = World.CreateBody(&myBodyDef);

	//TODO:: Andy says: Ik denk dat hier de widht en height
	Shape.SetAsBox((32.f / 2), (32.f / 2));

	boxFixtureDef.density = 100.f;
	boxFixtureDef.friction = 0.0f;
	boxFixtureDef.shape = &Shape;
	Body->CreateFixture(&boxFixtureDef);
}

void GameObject::createBoxDynamic(b2World & World)
{
	
	myBodyDef.type = b2_dynamicBody;

	Body = World.CreateBody(&myBodyDef);

	if (this->getHeight() < 1 || this->getWidth() < 1) {
		Shape.SetAsBox((32.f / 2), (32.f / 2));
	}
	else {
		Shape.SetAsBox(getHeight() / 2, getWidth() / 2);
	}


	boxFixtureDef.density = 100.f;
	boxFixtureDef.friction = 0.7f;
	boxFixtureDef.shape = &Shape;
	Body->CreateFixture(&boxFixtureDef);
}
