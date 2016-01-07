#pragma once

#include "Gun.h"

class Pistol : public Gun
{
public:
	Pistol(std::map<std::string, std::string>& properties, GameObjectContainer* gameObjectContainer);
	~Pistol();
};

