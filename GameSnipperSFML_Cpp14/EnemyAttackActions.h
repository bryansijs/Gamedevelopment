#pragma once
#include <string>
#include "GameObjectFactory.h"
class BaseEnemy;
class GameObjectFactory;
class EnemyAttackActions
{

public:
	EnemyAttackActions(BaseEnemy* obj);
	~EnemyAttackActions();

	BaseEnemy* obj;
	void Attack();
	void SingleShot();
	void SingleShotBig();
	void DualShot();
	void TripleShot();

	void SpreadShot();
	std::string direction;

	GameObjectFactory* gameObjectFactory;

};