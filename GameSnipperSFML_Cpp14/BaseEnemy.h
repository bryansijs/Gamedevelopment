#pragma once
#include "Unit.h"



class BaseEnemy : public Unit
{
private:

	Player* player;
	b2Vec2 vertices[3];
	b2FixtureDef myFixtureDef;

public:
	BaseEnemy();
	~BaseEnemy();
	BaseEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* goContainer);

	virtual void setProperties(std::map<std::string, std::string>& properties);

	b2PolygonShape  chain;
	sf::ConvexShape convex;
	int seeAngle;
	int seeLenght;

	b2Vec2 vecA;
	b2Vec2 vecB;

	void setVectorA(b2Vec2 vecA) { this->vecA = vecA; }
	b2Vec2 getVectorA() { return vecA; }

	void setVectorB(b2Vec2 vecB) { this->vecB = vecB; }
	b2Vec2 getVectorB() { return vecB; }

	void Update();

};

