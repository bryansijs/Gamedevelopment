#include "stdafx.h"
#include "RunnerEnemy.h"

#include "WanderMoveBehaviour.h"

RunnerEnemy::RunnerEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, b2World* world) :BaseEnemy{ dContainer, img,mContainer, gameObjectContainer }
{
	this->isCollidable = true;



	this->setSpeed(70.f);
	this->setBulletDamageBig(10);
	this->setBulletDamage(5);
	this->setMaxHealth(75);
	this->setHealth(75);



	this->setSeeLengt(300);
	this->setSeeWidth(25);

	this->setMaxWanderDistance(300);
	this->setMinWanderDistance(70);
	this->setDefaultWanderDistance(20);


	this->setBulletDamageBig(40);
	this->setBulletDamage(10);

	this->setProperties(properties);
	this->SetAnimationStates(4);
	this->createBoxDynamic(*world);
	this->CreateLineOfSight();

	this->setPattern();

	this->setAttackType(0);
	this->setPatternAmount(20);
	this->shotRate = 0.25f;


}
void RunnerEnemy::setPattern()
{
	this->PatternSet.insert(std::pair<std::string, float>("0103", 2.0f));
	this->PatternSet.insert(std::pair<std::string, float>("0020", 0.25f));

}

RunnerEnemy::~RunnerEnemy()
{
}
