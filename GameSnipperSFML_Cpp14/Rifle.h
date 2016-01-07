#pragma once

#include "Gun.h"

class Rifle : public Gun
{
public:
	Rifle(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer);
	~Rifle();
};

