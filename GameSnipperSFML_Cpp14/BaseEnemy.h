#pragma once
#include "Unit.h"



class BaseEnemy : public Unit
{
private:

	Player* player;
	b2Vec2 vertices[3];
	sf::ConvexShape* convex;
	bool create = true;
	b2PolygonShape  chain;
	b2FixtureDef myFixtureDef;
	b2Body* m_body;
	b2BodyDef* los;
public:
	BaseEnemy();
	~BaseEnemy();
	BaseEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* goContainer);
	virtual void setProperties(std::map<std::string, std::string>& properties);


	int seeAngle;
	int seeLenght;

	void Update();


	sf::ConvexShape& getConvex() { return *convex; }
};




