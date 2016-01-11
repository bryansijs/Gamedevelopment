#include "stdafx.h"
#include "BaseEnemy.h"
#include "Time.h"
#include "KeyMapping.h"
#include "Player.h"
#include <Box2D\Dynamics\b2Body.h>
#include <Box2D\Collision\b2Collision.h>
#include "FilterEnum.h"
#include "MoveBehaviour.h"
#include "EnemyDrawBehaviour.h"
#include "DrawContainer.h"
#include "AttackBehaviour.h"
#include "MoveContainer.h"
#include "EnemyAttackActions.h"
#include "FollowMoveBehaviour.h"
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

	this->mhpBar = new sf::RectangleShape(sf::Vector2f(60, 14));
	this->mhpBar->setFillColor(sf::Color(100, 100, 100, 128));

	this->hpBar = new sf::RectangleShape(sf::Vector2f(56, 10));
	this->hpBar->setFillColor(sf::Color(255, 0, 0, 128));


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

	this->setMaxHealth((properties.count("maxHealth")) ? std::stoi(properties["maxHealth"]) : 100);
	this->setHealth((properties.count("maxHealth")) ? std::stoi(properties["maxHealth"]) : 100);

	this->setBulletTexture((properties.count("bullet")) ? std::string(properties["bullet"]) : "bullet-blue");
	this->setBulletTextureBig((properties.count("bigbullet")) ? std::string(properties["bigbullet"]) : "bullet-big-red");
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

	b2Filter f = this->getBody()->GetFixtureList()->GetNext()->GetFilterData();

	f.categoryBits = ENEMY;
	this->getBody()->GetFixtureList()->GetNext()->SetFilterData(f);
	this->Action = new EnemyAttackActions(this);
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

		desiredAngle = atan2f(0, -seeLength * 2);
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
	this->mhpBar->setPosition(sf::Vector2f(this->getBody()->GetPosition().x - 16, this->getBody()->GetPosition().y - 30));
	this->hpBar->setPosition(sf::Vector2f(this->getBody()->GetPosition().x - 14, this->getBody()->GetPosition().y - 28));

	//56 is de groote dus dit is gelijk aan maxhp;

	float b = 56.0f / (float)this->getMaxHealth();
	float c = (float)this->getHealth() * b;

	this->hpBar->setSize(sf::Vector2f(c, 10));

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
				{
					this->lineOfSightConvex->setFillColor(sf::Color(250, 0, 0, 128));
					this->Attacking = true;
					if (this->target == nullptr)
					{
						this->target = dynamic_cast<Player*>(obj);
					}
				}
				else
				{
					this->Attacking = false;
				}

				if (!dynamic_cast<FollowMoveBehaviour*>(this->getMoveBehaviour()))
				{
					this->getMoveContainer()->RemoveBehaviour(this->getMoveBehaviour());
					this->SetMoveBehaviour({ new FollowMoveBehaviour(this) });
					this->getMoveContainer()->AddBehaviour(this->getMoveBehaviour());
				}
			}
		}
	}

	//if (dynamic_cast<AttackBehaviour*>(this->getMoveBehaviour()))
	if (Attacking)
		Action->Attack();

	if (patternAmount == 0)return;

	if (this->patternCount >= patternAmount)
	{
		patternCount = 0;

		patternIndex++;

		if (patternIndex >= this->PatternSet.size())
			patternIndex = 0;

		std::map<std::string, float>::iterator it;
		int i = 0;
		for (it = PatternSet.begin(); it != PatternSet.end(); it++)
		{
			if (i == patternIndex) {
				std::string patternInfo = it->first;

				this->attackType = (patternInfo[0] - '0') * 10 + (patternInfo[1] - '0');
				this->patternAmount = (patternInfo[2] - '0') * 10 + (patternInfo[3] - '0');
				this->shotRate = it->second;
				break;
			}
			i++;
		}

	}
}



void BaseEnemy::startContact(b2Fixture * fixture)
{

}

void BaseEnemy::endContact(b2Fixture * fixture)
{

}
