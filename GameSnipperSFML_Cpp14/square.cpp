#include "stdafx.h"
#include "square.h"
#include "Context.h"


square::square(Context* con, float x, float y) 
{
	BoxTexture.loadFromFile("box.png");
	this->context = con;

	this->setPosition(x, y);
}

square::~square()
{
}


