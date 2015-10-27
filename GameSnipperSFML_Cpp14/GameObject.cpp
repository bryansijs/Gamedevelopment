#include "stdafx.h"
#include "GameObject.h"

#include "DrawContainer.h"
#include "MoveContainer.h"
#include "NormalDrawBehaviour.h"
#include "MoveBehaviour.h"

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

