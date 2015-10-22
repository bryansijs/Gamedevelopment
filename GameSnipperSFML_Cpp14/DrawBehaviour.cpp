#include "stdafx.h"
#include "DrawBehaviour.h"

sf::Sprite DrawBehaviour::getCurrentImage() { return this->unitImage; }

Unit* DrawBehaviour::getUnit()
{
	
	return unit;
}

Game_Object* DrawBehaviour::getObject()
{

	return game_Object;
}