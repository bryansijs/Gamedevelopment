#pragma once
#include "Unit.h"
class EnemyAttackActions;
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
	bool Attacking = false;
	int seeWidth,seeLength;
	int attackType = 0;
	int patternCount = 0, patternAmount = 0, patternIndex = 0;
	int minWanderDistance,maxWanderDistance, defaultWanderDistance;
	int bulletDamage = 20, bulletDamageBig = 30;


	std::string bulletTexture, bulletTextureBig;

	void CreateVisibleLine();
	void CreateVectors();
	void startContact(b2Fixture * fixture);
	void endContact(b2Fixture * fixture);
	EnemyAttackActions* Action;



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
	float shotRate = 0.5f;
	float nextShot;

	int getAttacktType() { return attackType; }
	void setAttackType(int attacktype) { this->attackType = attackType; }

	int getPatternAmount() { return patternAmount; }
	void setPatternAmount(int patternAmount) { this->patternAmount = patternAmount; }

	int getPatternCount() { return patternCount; }
	void setPatternCount(int patternCount) { this->patternCount = patternCount; }

	int getPatternIndex() { return patternIndex; }
	void setPatternIndex(int patternIndex) { this->patternIndex = patternIndex; }

	std::string getBulletTexture() { return this->bulletTexture; }
	void setBulletTexture(std::string bulletTexture) { this->bulletTexture = bulletTexture; }
	
	std::string getBulletTextureBig() { return this->bulletTextureBig; }
	void setBulletTextureBig(std::string bulletTextureBig) { this->bulletTextureBig = bulletTextureBig; }

	int getBulletDamage() { return bulletDamage; }
	void setBulletDamage(int bulletDamage) { this->bulletDamage = bulletDamage; }

	int getBulletDamageBig() { return bulletDamageBig; }
	void setBulletDamageBig(int bulletDamageBig) { this->bulletDamageBig = bulletDamageBig; }

	std::map<std::string, float> PatternSet;

};




