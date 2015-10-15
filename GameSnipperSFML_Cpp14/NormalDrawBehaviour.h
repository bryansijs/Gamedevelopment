#pragma once
#include "DrawBehaviour.h"

class NormalDrawBehaviour : public DrawBehaviour
{
public:
	NormalDrawBehaviour(Unit* u, int refreshRate, std::string playerTextureURL);
	~NormalDrawBehaviour();

	virtual void getCurrentImage();
};

