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

	this->seeLength = (properties.count("seeLength")) ? std::stoi(properties["seeLength"]) : 250;
	this->seeWidth = (properties.count("seeWidth")) ? std::stoi(properties["seeWidth"]) : 100;

	this->setPosition(x, y);
	this->setSize(widht, height);

	this->setImageY((properties.count("yIndex")) ? std::stoi(properties["yIndex"]) : 0);
}

void BaseEnemy::CreateLineOfSight()
{
	this->lineOfSightFixtureDef = new b2FixtureDef();
	this->lineOfSightBodyDef = new b2BodyDef();
	this->lineOfSightConvex = new sf::ConvexShape{};
	this->lineOfSightConvex->setPointCount(3);

	lineOfSightBodyDef->position = this->getBody()->GetPosition();
	this->lineOfSightBodyDef->type = b2_dynamicBody;
	this->lineOfSightBody = this->world->CreateBody(lineOfSightBodyDef);

	vertices[0].Set(16, 16);
	vertices[1].Set(seeWidth, seeLength);
	vertices[2].Set(-seeWidth, seeLength);
	CreateVectors();

	lineOfSightFixtureDef->shape = &lineOfSightShape;
	lineOfSightFixtureDef->density = 100;
	lineOfSightFixtureDef->friction = 0.3f;
	lineOfSightFixtureDef->isSensor = true;
	lineOfSightBody->CreateFixture(lineOfSightFixtureDef);
}

void BaseEnemy::CreateVectors()
{
	float desiredAngle;
	switch (this->getIndexY())
	{
	case 0: {
		desiredAngle = atan2f(0, 0);
		convexVert[0].Set(16, 16);
		convexVert[1].Set(seeWidth, seeLength);
		convexVert[2].Set(-seeWidth, seeLength);
	}	break;
	case 1: {
		desiredAngle = atan2f(seeLength * 2, 0);
		convexVert[0].Set(16, 16);
		convexVert[1].Set(-seeLength, seeWidth);
		convexVert[2].Set(-seeLength, -seeWidth);
	}	break;
	case 2: {
		desiredAngle = atan2f(-seeLength * 2, 0);
		convexVert[0].Set(16, 16);
		convexVert[1].Set(seeLength, seeWidth);
		convexVert[2].Set(seeLength, -seeWidth);
	}	break;
	case 3: {

		desiredAngle = atan2f(0, -seeLength *2);
		convexVert[0].Set(16, 16);
		convexVert[1].Set(-seeWidth, -seeLength);
		convexVert[2].Set(seeWidth, -seeLength);
	}	break;


	default:
		break;
	}

	this->lineOfSightBody->SetTransform(this->getBody()->GetPosition(), desiredAngle);
	this->lineOfSightShape.Set(this->vertices, 3);
}


void BaseEnemy::CreateVisibleLine()
{
	this->lineOfSightConvex->setFillColor(sf::Color(255, 129, 0, 128));
	this->lineOfSightConvex->setPosition(sf::Vector2f(lineOfSightBody->GetPosition().x, lineOfSightBody->GetPosition().y));

	for (int i = 0; i < 3; i++)
		this->lineOfSightConvex->setPoint(i, sf::Vector2f(convexVert[i].x, convexVert[i].y));
}

void BaseEnemy::Update()
{
	this->CreateVectors();
	this->CreateVisibleLine();


	for (b2ContactEdge* ce = lineOfSightBody->GetContactList(); ce; ce = ce->next)
	{
		b2Contact* c = ce->contact;
		GameObject* obj = static_cast<GameObject*>(ce->other->GetUserData());
		if (dynamic_cast<Player*>(obj))
		{
			if (c->IsTouching())
				this->lineOfSightConvex->setFillColor(sf::Color(250, 0, 0, 128));
		}

	}
}


