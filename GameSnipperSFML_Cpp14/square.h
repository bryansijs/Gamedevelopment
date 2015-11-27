#pragma once
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include "GameObject.h"

class Context;
class square : public GameObject
{
public:
	square(Context* con);
	~square();

	b2Body* getBody() { return this->Body; };

	Context* context;
	b2World* world;
	sf::Texture BoxTexture;

};

