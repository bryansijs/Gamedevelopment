#include "stdafx.h"
#include "BaseEnemy.h"
#include "Time.h"
#include "KeyMapping.h"
#include "Player.h"
#include <Box2D\Dynamics\b2Body.h>
#include <Box2D\Collision\b2Collision.h>
#include "FilterEnum.h"
#include "Tile.h"
#include "MoveBehaviour.h"
#include "EnemyDrawBehaviour.h"
#include "DrawContainer.h"
BaseEnemy::BaseEnemy()
{
}


BaseEnemy::~BaseEnemy()
{
}


BaseEnemy::BaseEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer) :Unit{ dContainer, img,mContainer, gameObjectContainer } {

	this->getDrawContainer()->RemoveBehaviour(this->getDrawBehaviour());
	this->setDrawBehaviour({ new EnemyDrawBehaviour(this, 10, "./Resources/sprites/" + img) });
	this->getDrawContainer()->AddBehaviour(this->getDrawBehaviour());

//	this->hpBar = new sf::RectangleShape(sf::Vector2f(100, 20));
//	this->hpBar->setFillColor(sf::Color(100, 100, 100, 128));
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
	this->setSpeed((properties.count("speed")) ? std::stoi(properties["speed"]) : 40);

	this->setMinWanderDistance((properties.count("minWander")) ? std::stoi(properties["minWander"]) : 10);
	this->setMaxWanderDistance((properties.count("maxWander")) ? std::stoi(properties["maxWander"]) : 100);
	this->setDefaultWanderDistance((properties.count("defaultWander")) ? std::stoi(properties["defaultWander"]) : 20);

}

void BaseEnemy::CreateLineOfSight()
{
	this->lineOfSightFixtureDef = new b2FixtureDef();
	this->lineOfSightConvex = new sf::ConvexShape{};
	this->lineOfSightConvex->setPointCount(3);

	vertices[0].Set(16, 16);
	vertices[1].Set(seeWidth, seeLength);
	vertices[2].Set(-seeWidth, seeLength);
	CreateVectors();

	lineOfSightFixtureDef->shape = &lineOfSightShape;
	lineOfSightFixtureDef->density = 100;
	lineOfSightFixtureDef->friction = 0.3f;
	lineOfSightFixtureDef->isSensor = true;

	this->getBody()->CreateFixture(lineOfSightFixtureDef);
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

	this->getBody()->SetTransform(this->getBody()->GetPosition(), desiredAngle);
	this->lineOfSightShape.Set(this->vertices, 3);
}


void BaseEnemy::CreateVisibleLine()
{
	this->lineOfSightConvex->setFillColor(sf::Color(255, 129, 0, 128));
	this->lineOfSightConvex->setPosition(sf::Vector2f(this->getBody()->GetPosition().x, this->getBody()->GetPosition().y));
//	this->hpBar->setPosition(sf::Vector2f(this->getBody()->GetPosition().x + this->getHeight()/2, this->getBody()->GetPosition().y) );

	for (int i = 0; i < 3; i++)
		this->lineOfSightConvex->setPoint(i, sf::Vector2f(convexVert[i].x, convexVert[i].y));
}

void BaseEnemy::Update()
{
	this->CreateVectors();
	this->CreateVisibleLine();

	
	for (b2ContactEdge* ce = this->getBody()->GetContactList(); ce; ce = ce->next)
	{

		b2Contact* c = ce->contact;
		b2Fixture* fixtureA = c->GetFixtureA();
		b2Fixture* fixtureB = c->GetFixtureB();
		if (fixtureA->IsSensor() || fixtureB->IsSensor()) {
			GameObject* obj = static_cast<GameObject*>(ce->other->GetUserData());
			if (dynamic_cast<Player*>(obj))
			{
				if (c->IsTouching())
					this->lineOfSightConvex->setFillColor(sf::Color(250, 0, 0, 128));
			}
		}
	}
}



void BaseEnemy::startContact(b2Fixture * fixture)
{

}

void BaseEnemy::endContact(b2Fixture * fixture)
{

}