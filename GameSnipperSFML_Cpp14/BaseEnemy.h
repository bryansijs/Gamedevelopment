#pragma once
#include "Unit.h"
#include "Player.h"
//#include "EnemyAttackActions.h"

class EnemyAttackActions;
class BaseEnemy : public Unit
{
private:
	b2Vec2 vertices[3];
	b2Vec2 convexVert[3];
	b2Body* linearBody;
	b2BodyDef* linearBodyDef;
	sf::ConvexShape lineOfSightConvex;
	sf::RectangleShape mhpBar;
	sf::RectangleShape hpBar;
	b2PolygonShape  lineOfSightShape;
	b2FixtureDef* lineOfSightFixtureDef;
	Player* target;
	bool Attacking = false;
	bool Aggressive = false;
	int seeWidth, seeLength;
	int attackType = 0;
	int patternCount = 0, patternAmount = 0, patternIndex = 0;
	int minWanderDistance, maxWanderDistance, defaultWanderDistance;
	int bulletDamage = 20, bulletDamageBig = 30;


	float aggressiveRate = 2.0f;
	float aggressiveTime = 0.0f;

	std::string bulletTexture, bulletTextureBig;

	void CreateVisibleLine();
	void CreateVectors();
	void startContact(b2Fixture * fixture);
	void endContact(b2Fixture * fixture);
	EnemyAttackActions* Action;

	void updateBehaviour(bool shouldCheck);

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

	sf::ConvexShape getLineOfSightConvex() { return lineOfSightConvex; }
	sf::RectangleShape getMaxHpBar() { return mhpBar; }
	sf::RectangleShape getHpBar() { return hpBar; }
	float shotRate = 0.5f;
	float nextShot;
	void addAggressiveTime(float time) { aggressiveTime += time; }
	void setAttacking() { this->Attacking = true; }

	Player* getTarget() { return target; }
	void setTarget(Player* target) { this->target = target; }

	int getAttacktType() { return attackType; }
	void setAttackType(int attacktype) { this->attackType = attacktype; }

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


	int getSeeLength() { return this->seeLength; };
	void setSeeLength(int seeLength) { this->seeLength = seeLength; };

	int getSeeWidth() { return this->seeWidth; }
	void setSeeWidth(int seeWidth) { this->seeWidth = seeWidth; };

	std::map<std::string, float> PatternSet;

};




