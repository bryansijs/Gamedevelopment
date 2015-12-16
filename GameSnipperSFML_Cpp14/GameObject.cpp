#include "stdafx.h"
#include "GameObject.h"

#include "DrawContainer.h"
#include "MoveContainer.h"
#include "GameObjectContainer.h"

#include "NormalDrawBehaviour.h"
#include "WanderMoveBehaviour.h"
#include "MoveBehaviour.h"
#include <Box2D\Box2D.h>

#include "Tile.h"
#include "EndTile.h"

void GameObject::Destroy()
{
	this->moveContainer->RemoveBehaviour(moveBehaviour);
	this->drawContainer->RemoveBehaviour(drawBehaviour);
	this->gameObjectContainer->RemoveObject(this);

	isFlaggedForDelete = true;
}

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

void GameObject::createBoxStatic(b2World& World)
{
	myBodyDef.type = b2_staticBody;

	Body = World.CreateBody(&myBodyDef);

	if (this->getHeight() < 1 || this->getWidth() < 1) {
		Shape.SetAsBox((32.f / 2), (32.f / 2));
	}
	else {
		b2Vec2 vertices[4];
		vertices[0].Set(0, 0);
		vertices[1].Set(0, this->getHeight());
		vertices[2].Set(this->getWidth(), this->getHeight());
		vertices[3].Set(this->getWidth(),0);
		this->Shape.Set(vertices, 4);
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
		b2Vec2 vertices[4];
		vertices[0].Set(-16, -16);
		vertices[1].Set(-16, this->getHeight() + -16);
		vertices[2].Set(this->getWidth() + -16, this->getHeight() + -16);
		vertices[3].Set(this->getWidth() + -16, -16);
		this->Shape.Set(vertices, 4);
	}


	boxFixtureDef.density = 100.f;
	boxFixtureDef.friction = 0.7f;
	boxFixtureDef.shape = &Shape;
	Body->CreateFixture(&boxFixtureDef);
	Body->SetUserData(this);
}

void GameObject::createBoxSenor(b2World & World)
{
	
	myBodyDef.type = b2_staticBody;

	Body = World.CreateBody(&myBodyDef);

	if (this->getHeight() < 1 || this->getWidth() < 1) {
		Shape.SetAsBox((32.f / 2), (32.f / 2));
	}
	else {
		b2Vec2 vertices[4];
		vertices[0].Set(-16, -16);
		vertices[1].Set(-16, this->getHeight() + -16);
		vertices[2].Set(this->getWidth() + -16, this->getHeight() + -16);
		vertices[3].Set(this->getWidth() + -16, -16);
		this->Shape.Set(vertices, 4);
	}

	boxFixtureDef.density = 100.f;
	boxFixtureDef.friction = 0.0f;
	boxFixtureDef.shape = &Shape;
	boxFixtureDef.isSensor = true;
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