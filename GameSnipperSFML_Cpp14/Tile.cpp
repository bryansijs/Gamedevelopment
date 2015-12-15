#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
}


Tile::~Tile()
{
}

void Tile::createStaticBody(b2World& world)
{
	
	//check of locatie niet 0 is. 
	myBodyDef.position = b2Vec2(this->getPositionX(), this->getPositionY());
	myBodyDef.type = b2_staticBody;

	Body = world.CreateBody(&myBodyDef);

	Shape.SetAsBox((32.f / 2), (32.f / 2));	//Als een tile altijd 32 x 32 is kan dit blijven staan. 


	boxFixtureDef.density = 100.f;
	boxFixtureDef.friction = 0.0f;
	boxFixtureDef.shape = &Shape;
	Body->CreateFixture(&boxFixtureDef);
}
