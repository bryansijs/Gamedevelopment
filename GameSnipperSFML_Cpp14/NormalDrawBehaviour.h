#pragma once
#include "DrawBehaviour.h"

class NormalDrawBehaviour : public DrawBehaviour
{
public:
	NormalDrawBehaviour(Unit* u, int refreshRate, std::string playerTextureURL);
	NormalDrawBehaviour(Game_Object* object, int refreshRate, std::string objectTextureURL);
	~NormalDrawBehaviour();

	sf::Sprite getCurrentImage();
};

