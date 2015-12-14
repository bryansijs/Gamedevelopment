#include "stdafx.h"
#include "BaseEnemy.h"
#include "Time.h"
#include "KeyMapping.h"
#include "Player.h"
#include <Box2D\Dynamics\b2Body.h>
#include <Box2D\Collision\b2Collision.h>
BaseEnemy::BaseEnemy()
{
}


BaseEnemy::~BaseEnemy()
{
}


BaseEnemy::BaseEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer) :Unit{ dContainer, img,mContainer, gameObjectContainer } {

}


void BaseEnemy::setProperties(std::map<std::string, std::string>& properties)
{
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);

	this->seeLenght = (properties.count("seeLenght")) ? std::stoi(properties["seeLenght"]) : 250;
	this->seeAngle = (properties.count("seeAngle")) ? std::stoi(properties["seeAngle"]) : 100;

	this->setPosition(x, y);
	this->setSize(widht, height);

	this->setImageY((properties.count("yIndex")) ? std::stoi(properties["yIndex"]) : 0);

	//Laten we een Line  of sight maken. 
	this->los = new b2BodyDef();
	this->convex = new sf::ConvexShape{};
	this->convex->setPointCount(3);
	this->convex->setFillColor(sf::Color(255, 129, 0, 128));




}

void BaseEnemy::Update()
{
	if (this->player == nullptr) {

		for (b2Body * b = world->GetBodyList(); b != NULL; b = b->GetNext()) {
			GameObject* wrapper = reinterpret_cast<GameObject*>(b->GetUserData());
			if (dynamic_cast<Player*>(wrapper))
			{
				this->player = dynamic_cast<Player*>(wrapper);
				break;
			}
		}
	}
	
	int b = this->getIndexY();
	los->position = this->getBody()->GetPosition();
	switch (b)
	{
	case 0: {
		vertices[0].Set(16, 16);
		vertices[1].Set(seeAngle, seeLenght);
		vertices[2].Set(-seeAngle, seeLenght);
	}	break;
	case 1: {
		vertices[0].Set(16, 16);
		vertices[1].Set(-seeLenght, seeAngle);
		vertices[2].Set(-seeLenght, -seeAngle);
	}	break;
	case 2: {
		vertices[0].Set(16, 16);
		vertices[1].Set(seeLenght, seeAngle);
		vertices[2].Set(seeLenght,-seeAngle);
	}	break;
	case 3: {
		vertices[0].Set(16, 16);
		vertices[1].Set(-seeAngle, -seeLenght);
		vertices[2].Set(seeAngle, -seeLenght);
	}	break;


	default:
		break;
	}

	this->chain.Set(this->vertices, 3);
	if (this->create)
	{
		this->los->type = b2_dynamicBody;
		this->m_body = this->world->CreateBody(los);
		this->myFixtureDef.shape = &chain;
		this->myFixtureDef.density = 100.f;
		this->myFixtureDef.friction = 0.0f;
		this->myFixtureDef.isSensor = true;

		this->m_body->CreateFixture(&myFixtureDef);
		this->create = false;
	}

	this->m_body->SetTransform(los->position, 0);
	
	this->convex->setFillColor(sf::Color(255, 129, 0, 128));
	this->convex->setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));

	this->convex->setPoint(0, sf::Vector2f(chain.GetVertex(0).x, chain.GetVertex(0).y));
	this->convex->setPoint(1, sf::Vector2f(chain.GetVertex(1).x, chain.GetVertex(1).y));
	this->convex->setPoint(2, sf::Vector2f(chain.GetVertex(2).x, chain.GetVertex(2).y));

	for (b2ContactEdge* ce = m_body->GetContactList(); ce; ce = ce->next)
	{
		b2Contact* c = ce->contact;
		if (this->player == static_cast<Player*>(ce->other->GetUserData()))
		{
			if (c->IsTouching())
				this->convex->setFillColor(sf::Color(000, 129, 0, 128));
		}
	}
}