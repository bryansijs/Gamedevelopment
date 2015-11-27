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

void GameObject::move()
{
	this->moveBehaviour->Update();
}



void GameObject::doAction()
{

}

bool GameObject::isColliding(std::vector<Tile*> tiles, sf::Vector2f velocity)
{
	//for (int i = 0; i < tiles.size(); i++) {

	//	if (tiles.at(i)->isCollidable) {
	//		if (getPosition().x + velocity.x < (tiles.at(i)->x_Position + 28) &&
	//			(getPosition().x + velocity.x + 28) > tiles.at(i)->x_Position &&
	//			getPosition().y + velocity.y < (tiles.at(i)->y_Position + 12) &&
	//			(getPosition().y + velocity.y + 32) > tiles.at(i)->y_Position) {
	//			return true;
	//		}
	//	}
	//}
	return false;
}

void GameObject::createBoxStatic(b2World& World)
{

	
	myBodyDef.type = b2_staticBody;

	Body = World.CreateBody(&myBodyDef);

	Shape.SetAsBox((32.f / 2), (32.f / 2));

	boxFixtureDef.density = 1.f;
	boxFixtureDef.friction = 0.0f;
	boxFixtureDef.shape = &Shape;
	Body->CreateFixture(&boxFixtureDef);
}

void GameObject::createBoxDynamic(b2World & World)
{
	
	myBodyDef.type = b2_dynamicBody;

	Body = World.CreateBody(&myBodyDef);

	Shape.SetAsBox((32.f / 2), (32.f / 2));

	boxFixtureDef.density = 1.f;
	boxFixtureDef.friction = 0.7f;
	boxFixtureDef.shape = &Shape;
	Body->CreateFixture(&boxFixtureDef);
}
