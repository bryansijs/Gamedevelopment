#include "stdafx.h"
#include "StoryTile.h"
#include "Player.h"


StoryTile::StoryTile(GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, b2World * world)
{
	this->setProperties(properties);
	this->createBoxSenor(*world);
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

	for (size_t i = 1; i <= std::stoi(properties["Lines"]); i++)
	{
		std::string temp = "Line";
		temp += std::to_string(i);

		if (properties.find(temp) != properties.end())
		{
			storys.push_back(properties[temp]);
		}
	}
}

void StoryTile::doAction()
{
	if (!told)
	{
		for (size_t i = 0; i < storys.size(); i++)
		{
			storylineManager->Add(storys[i]);
		}

		told = true;
	}
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

void StoryTile::setStorylineManager(StorylineManager* storylineManager)
{
	this->storylineManager = storylineManager;
}
