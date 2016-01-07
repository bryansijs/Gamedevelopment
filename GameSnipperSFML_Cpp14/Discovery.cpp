#include "stdafx.h"
#include "Discovery.h"
#include "GameObjectContainer.h"
#include "DrawContainer.h"
#include <algorithm>

Discovery::Discovery(DrawContainer* container, GameObjectContainer * gameObjectContainer, std::map<std::string, std::string>& properties, std::vector<Tile*>& tiles, b2World * world) :GameObject { container}
{
	this->setProperties(properties);
	this->createBoxSenor(*world);
}

Discovery::~Discovery()
{
}

void Discovery::setProperties(std::map<std::string, std::string>& properties)
{
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);
	this->setVisibleId(std::stoi(properties["VisibleId"]));

	this->setPosition(x, y);
	this->setSize(widht, height);
}

void Discovery::doAction()
{
	if (!this->getDrawContainer()->checkIfidIsDiscoverd(this->getVisibleId())) {
		this->getDrawContainer()->addDiscoveryId(this->getVisibleId());
	}
}

void Discovery::startContact(b2Fixture * fixture)
{
	this->doAction();
}

void Discovery::endContact(b2Fixture * fixture)
{
}
