#include "stdafx.h"
#include "square.h"
#include "Context.h"


square::square(Context* con) 
{
	BoxTexture.loadFromFile("box.png");
	this->context = con;
}

square::~square()
{
}


