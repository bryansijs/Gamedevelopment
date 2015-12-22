#include "stdafx.h"
#include "DiscoverTile.h"
#include "Level.h"

DiscoverTile::DiscoverTile(GameObjectContainer * gameObjectContainer, std::map<std::string, std::string>& properties, b2World * world, Level* lv)
{
	this->level = lv;
	this->setProperties(properties);
	this->createBoxSenor(*world);
}

DiscoverTile::~DiscoverTile()
{

}

void DiscoverTile::setProperties(std::map<std::string, std::string>& properties)
{
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);
	DiscoverId = std::stoi(properties["Layer"]);
	this->setPosition(x, y);
	this->setSize(widht, height);

}

void DiscoverTile::doAction()
{
}

void DiscoverTile::startContact(b2Fixture * fixture)
{
	level->addDiscoverdLayer(DiscoverId);
}

void DiscoverTile::endContact(b2Fixture * fixture)
{
}
