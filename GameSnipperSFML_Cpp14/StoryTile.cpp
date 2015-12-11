#include "stdafx.h"
#include "StoryTile.h"
#include "Player.h"


StoryTile::StoryTile(GameObjectContainer* gameObjectContainer) : GameObject{ gameObjectContainer }
{
}


StoryTile::~StoryTile()
{
}

void StoryTile::setProperties(std::map<std::string, std::string>& properties)
{
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);

	this->setPosition(x, y);
	this->setSize(widht, height);
}

void StoryTile::doAction()
{
	std::cout << "test";


	told = true;
}

void StoryTile::startContact(b2Fixture * fixture)
{
	GameObject* pal = static_cast<Player*>(fixture->GetBody()->GetUserData());
	if (dynamic_cast<Player*> (pal)) {
		this->doAction();
	}
}

void StoryTile::endContact(b2Fixture * fixture)
{

}
