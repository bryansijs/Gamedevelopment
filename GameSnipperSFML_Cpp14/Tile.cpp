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

	b2Vec2 vertices[4];
	vertices[0].Set(0, 0);
	vertices[1].Set(0, 32);
	vertices[2].Set(32, 32);
	vertices[3].Set(32, 0);
	this->Shape.Set(vertices, 4);

	boxFixtureDef.density = 10.f;
	boxFixtureDef.friction = 0.0f;
	boxFixtureDef.shape = &Shape;
	Body->CreateFixture(&boxFixtureDef);

}
