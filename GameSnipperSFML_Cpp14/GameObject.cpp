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
	//this->sbuffer.loadFromFile("Resources/sfx/hit.ogg");
	//this->sfx.setBuffer(this->sbuffer);
}

void GameObject::Load(std::string filename, bool dynamic)
{
	/*this->texture->loadFromFile("Resources/sprites/" + filename);
	this->setTexture(*this->texture);

	this->bodyDef = new b2BodyDef();
	if (dynamic)
	{
		this->bodyDef->type = b2_dynamicBody;
	}
	else
	{
		this->bodyDef->type = b2_staticBody;
	}
	this->bodyDef->position.Set(this->getPosition().x, this->getPosition().y);
	this->body = this->world->CreateBody(this->bodyDef);

	this->shape = new b2PolygonShape();
	this->shape->SetAsBox(this->texture->getSize().x * 0.5f - b2_polygonRadius, this->texture->getSize().y * 0.5f - b2_polygonRadius);

	this->fixtureDef = new b2FixtureDef();
	this->fixtureDef->shape = this->shape;

	if (dynamic)
	{
		this->fixtureDef->density = 1.0f;
		this->fixtureDef->friction = 0.3f;
		this->body->CreateFixture(this->fixtureDef);
	}
	else
	{
		this->body->CreateFixture(this->shape, 0);
	}*/
}


void GameObject::Handle()
{
	/*float x = 0, y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		x = -100;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		y = 100;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		y = -100;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		x = 100;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->sfx.play();
	}


	MoveUnit(x, y);
	*/
}

void GameObject::MoveUnit(float x, float y)
{
	/*b2Vec2 vel = body->GetLinearVelocity();

/*	switch (moveState)
	{
	case MS_LEFT:  desiredVel = -5; break;
	case MS_STOP:  desiredVel = 0; break;
	case MS_RIGHT: desiredVel = 5; break;
	}
	vel.y = y;
	vel.x = x;

	

	this->body->SetLinearVelocity(vel);
	*/

}

bool GameObject::Update(sf::RenderWindow* window)
{
	

	/*b2Vec2 pos = this->body->GetPosition();
	float32 rot = this->body->GetAngle();
this->setPosition(pos.x, -pos.y);
	this->setRotation(rot);*/
	return true;
}
void GameObject::Collision(GameObject* entity)
{
}

bool GameObject::CheckCollision(GameObject* entity){
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

GameObject::~GameObject()
{
	/*delete this->texture;
	delete this->bodyDef;
	delete this->shape;
	delete this->fixtureDef;*/
}
