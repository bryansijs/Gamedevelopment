#pragma once
#pragma once
#include <iostream>
#include <string>
#include  <memory>
#include <json\json.h>
#include "GameObject.h"
class GameObject;
class DrawContainer;


class GameObjectFactory
{
public:
	GameObjectFactory(DrawContainer *drawContainer);
	GameObjectFactory();
	~GameObjectFactory();

	GameObject* Create(Json::Value root);


private:
	DrawContainer *drawContainer;
};

