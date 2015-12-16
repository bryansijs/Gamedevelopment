#pragma once
#include "Unit.h"



class BaseEnemy : public Unit
{
private:

	Player* player;
	b2Vec2 vertices[3];
	b2Vec2 convexVert[3];
	sf::ConvexShape* lineOfSightConvex;

	b2PolygonShape  lineOfSightShape;
	b2FixtureDef* lineOfSightFixtureDef;
	b2Body* lineOfSightBody;
	b2BodyDef* lineOfSightBodyDef;

	int seeWidth;
	int seeLength;

	void CreateVisibleLine();
	void CreateVectors();
public:
	BaseEnemy();
	~BaseEnemy();
	BaseEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* goContainer);

	virtual void setProperties(std::map<std::string, std::string>& properties);
	void CreateLineOfSight();
	void Update();

	sf::ConvexShape& getLineOfSightConvex() { return *lineOfSightConvex; }
};




