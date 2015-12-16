#include "stdafx.h"
#include "BaseEnemy.h"
#include "Time.h"
#include "KeyMapping.h"
#include "Player.h"
#include <Box2D\Dynamics\b2Body.h>
#include <Box2D\Collision\b2Collision.h>


#include "MoveBehaviour.h"
BaseEnemy::BaseEnemy()
{
}


BaseEnemy::~BaseEnemy()
{
}


BaseEnemy::BaseEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer) :Unit{ dContainer, img,mContainer, gameObjectContainer } {
	this->setSpeed(40.0f);

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
}

void BaseEnemy::CreateLineOfSight()
{
	this->myFixtureDef = new b2FixtureDef();
	//Laten we een Line  of sight maken. 
	this->los = new b2BodyDef();
	this->convex = new sf::ConvexShape{};
	this->convex->setPointCount(3);

	los->position = this->getBody()->GetPosition();
	this->los->type = b2_dynamicBody;
	this->m_body = this->world->CreateBody(los);
	CreateVectors();


	myFixtureDef->shape = &chain;
	myFixtureDef->density = 100;
	myFixtureDef->friction = 0.3f;
	myFixtureDef->isSensor = true;
	myFixture  = m_body->CreateFixture(myFixtureDef);
}

void BaseEnemy::CreateVectors()
{
	int b = this->getIndexY();

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
		vertices[2].Set(seeLenght, -seeAngle);
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

	//
	if (m_body->GetFixtureList() != nullptr) {


		m_body->DestroyFixture(myFixture);

		myFixtureDef->shape = &chain;
		myFixtureDef->density = 100;
		myFixtureDef->friction = 0.3f;
		myFixtureDef->isSensor = true;
		myFixture =	m_body->CreateFixture(myFixtureDef);
	}



}

void BaseEnemy::AddPlayer()
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
}

void BaseEnemy::Update()
{
	if (this->player == nullptr)
		AddPlayer();


	this->los->position = this->getBody()->GetPosition();
	this->m_body->SetTransform(los->position, 0);

	CreateVectors();

	this->convex->setFillColor(sf::Color(255, 129, 0, 128));
	this->convex->setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));

	b2PolygonShape* s = (b2PolygonShape*)m_body->GetFixtureList()->GetShape();
	int vertextCount = s->GetVertexCount();
	this->convex->setPointCount(vertextCount);

	for (int i = 0; i < vertextCount; i++)
		this->convex->setPoint(i, sf::Vector2f(s->GetVertex(i).x, s->GetVertex(i).y));



	for (b2ContactEdge* ce = m_body->GetContactList(); ce; ce = ce->next)
	{
		std::cout << "stuff" << std::endl;
		b2Contact* c = ce->contact;

		GameObject* obj = static_cast<GameObject*>(ce->other->GetUserData());
		if (dynamic_cast<Player*>(obj))
		{
			if (c->IsTouching())
				std::cout << "Tough of red" << std::endl;
			//this->convex->setFillColor(sf::Color(250, 0, 0, 128));
		}

	}


}


