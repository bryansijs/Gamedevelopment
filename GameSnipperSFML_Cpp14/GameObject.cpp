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

void GameObject::doAction(Player * player)
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

void GameObject::createBoxStatic(b2World& World)
{	
	myBodyDef.type = b2_staticBody;

	Body = World.CreateBody(&myBodyDef);

	if (this->getHeight() < 1 || this->getWidth() < 1) {
		Shape.SetAsBox((32.f / 2), (32.f / 2));
	}
	else {
		Shape.SetAsBox(getHeight() / 2, getWidth() / 2);
	}

	boxFixtureDef.density = 100.f;
	boxFixtureDef.friction = 0.0f;
	boxFixtureDef.shape = &Shape;
	Body->CreateFixture(&boxFixtureDef);
	Body->SetUserData(this);
}

void GameObject::createBoxDynamic(b2World & World)
{
	
	myBodyDef.type = b2_dynamicBody;

	Body = World.CreateBody(&myBodyDef);

	if (this->getHeight() < 1 || this->getWidth() < 1) {
		Shape.SetAsBox((30.f / 2), (30.f / 2));
	}
	else {
		Shape.SetAsBox((getHeight() - 2) / 2, (getWidth() - 2) / 2);
	}


	boxFixtureDef.density = 100.f;
	boxFixtureDef.friction = 0.7f;
	boxFixtureDef.shape = &Shape;
	Body->CreateFixture(&boxFixtureDef);
	Body->SetUserData(this);
}

void GameObject::startContact(b2Fixture* fixture)
{
	// het gecollide object is terug te vinden in fixture fixture->GetBody()->GetUserData();

}

void GameObject::endContact(b2Fixture* fixture)
{

}
