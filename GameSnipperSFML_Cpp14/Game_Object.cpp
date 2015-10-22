#include "stdafx.h"
#include "Game_Object.h"
#include "NormalDrawBehaviour.h"

Game_Object::Game_Object(std::vector<DrawBehaviour*>* draws, std::string textureUrl)
{
	this->allDrawBehaviours = draws;
	this->drawBehaviour = { new NormalDrawBehaviour(this, 10, "./Resources/sprites/"+textureUrl) };
	this->allDrawBehaviours->push_back(this->drawBehaviour);
}


Game_Object::Game_Object()
{
}


Game_Object::~Game_Object()
{
}

void Game_Object::Update()
{
}

void Game_Object::setDrawBehaviour(DrawBehaviour* newDrawBehaviour)
{
	//Verwijder uit lijst. 
	this->drawBehaviour = newDrawBehaviour;
}