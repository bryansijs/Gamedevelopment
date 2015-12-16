#include "stdafx.h"
#include "DiscoverTile.h"


DiscoverTile::DiscoverTile(GameObjectContainer * gameObjectContainer, std::map<std::string, std::string>& properties, b2World * world)
{
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

	this->setPosition(x, y);
	this->setSize(widht, height);

}

void DiscoverTile::doAction()
{
}

void DiscoverTile::startContact(b2Fixture * fixture)
{
}

void DiscoverTile::endContact(b2Fixture * fixture)
{
}
