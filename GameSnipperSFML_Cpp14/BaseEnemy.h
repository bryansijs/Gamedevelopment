#pragma once
#include "Unit.h"

class BaseEnemy : public Unit
{
private:
	b2Vec2 vertices[3];
	b2Vec2 convexVert[3];
	sf::ConvexShape* lineOfSightConvex;
	sf::RectangleShape* mhpBar;
	sf::RectangleShape* hpBar;
	b2PolygonShape  lineOfSightShape;
	b2FixtureDef* lineOfSightFixtureDef;

	int seeWidth;
	int seeLength;

	int minWanderDistance;
	int maxWanderDistance;
	int defaultWanderDistance;
	void CreateVisibleLine();
	void CreateVectors();
	void startContact(b2Fixture * fixture);
	void endContact(b2Fixture * fixture);


	float shotRate = 0.5f;
	float nextShot;
public:
	BaseEnemy();
	~BaseEnemy();
	BaseEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* goContainer);

	virtual void setProperties(std::map<std::string, std::string>& properties);
	void CreateLineOfSight();
	void Update();

	void setMinWanderDistance(int minWanderDistance) { this->minWanderDistance = minWanderDistance; }
	void setMaxWanderDistance(int maxWanderDistance) { this->maxWanderDistance = maxWanderDistance; }
	void setDefaultWanderDistance(int defaultWanderDistance) { this->defaultWanderDistance = defaultWanderDistance; }

	int getMinWanderDistance() { return minWanderDistance; }
	int getMaxWanderDistance() { return maxWanderDistance; }
	int getDefaultWanderDistance() { return defaultWanderDistance; }

	sf::ConvexShape& getLineOfSightConvex() { return *lineOfSightConvex; }
	sf::RectangleShape& getMaxHpBar() { return *mhpBar; }
	sf::RectangleShape& getHpBar() { return *hpBar; }
	void Attack();

};




