#include "stdafx.h"
#include "NormalDrawBehaviour.h"
#include <iostream>

NormalDrawBehaviour::NormalDrawBehaviour(Unit* u, int refreshRate, std::string playerTextureURL)
{
	this->unit = u;

	if (!unitTexture.loadFromFile(playerTextureURL)) {
		std::cout << "Error could not load player image" << std::endl;
	}
	unitImage.setTexture(unitTexture);
}

NormalDrawBehaviour::~NormalDrawBehaviour()
{
}

void NormalDrawBehaviour::getCurrentImage()
{
}
