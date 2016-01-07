#include "stdafx.h"
#include "Game_Switch.h"
#include "Tile.h"
#include <iterator> 
#include "GameObjectContainer.h"
#include "Door.h"
#include "DrawContainer.h"

Game_Switch::Game_Switch()
{
}


Game_Switch::~Game_Switch()
{
}


	void Game_Switch::setProperties(std::map<std::string, std::string>& properties) {

	this->hazardIndex = (properties.count("hazardIndex")) ? std::stoi(properties["hazardIndex"]) : -1;
	this->doorIndex = (properties.count("doorId")) ? std::stoi(properties["doorId"]) : -1;

	this->isOn = (properties.count("state")) ? std::stoi(properties["state"]) : 0;
	this->ofState = (properties.count("ofIndex")) ? std::stoi(properties["ofIndex"]) : 0;
	this->onState = (properties.count("onIndex")) ? std::stoi(properties["onIndex"]) : 2;
	this->needKey = (properties.count("needKey")) ? std::stoi(properties["needKey"]) : 0;
	this->isCollidable = (properties.count("isCollidable")) ? std::stoi(properties["isCollidable"]) : 0;
	this->setVisibleId((properties.count("VisibleId")) ? std::stoi(properties["VisibleId"]) : 0);

	this->xOfIndex = (properties.count("ofXIndex")) ? std::stoi(properties["ofXIndex"]) : -1;
	this->setImageX((properties.count("xIndex")) ? std::stoi(properties["xIndex"]) : 0);

	if (this->isOn)
		this->setImageY(onState);
	else
		this->setImageY(ofState);

	this->shouldUpdate = true;

	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);


	this->setPosition(x, y);
	this->setSize(widht, height);
}

Game_Switch::Game_Switch(DrawContainer* container, GameObjectContainer *gameObjectContainer, std::string img, std::map<std::string, std::string>& properties, std::vector<Tile*>& tileList, b2World* world) :GameObject{ container,gameObjectContainer, img } {
	this->setProperties(properties);
	this->setTiles(tileList);
	this->createBoxStatic(*world);
};


Game_Switch::Game_Switch(GameObjectContainer *gameObjectContainer, std::map<std::string, std::string>& properties, std::vector<Tile*>& tileList, b2World* world) :GameObject{ gameObjectContainer } {
	
	this->setProperties(properties);
	
	this->setTiles(tileList);
	this->createBoxStatic(*world);
};

void Game_Switch::doAction(Player* player)
{
	if (this->getDrawContainer()->checkIfidIsDiscoverd(this->getVisibleId())) {
		if (needKey && !usedKey)
		{
			if (player->getKey() > 0) {
				player->removeKey();
				this->setImageX(xOfIndex);
				this->usedKey = true;
			}
			else
				return;
		}

		setState();
		shouldUpdate = true;
	}
}


void Game_Switch::Update()
{
	if (shouldUpdate != true) return;

	shouldUpdate = false;
	if (hazardIndex >= 0) {
		setHazardState();
	}

	if (doorIndex >= 0) {
		setDoorState();
	}
}

void Game_Switch::setHazardState()
{
	for (int i = 0; i < HazardList.size(); i++)
	{
		HazardList.at(i)->hazardState = !this->getState();
		HazardList.at(i)->isVisible = !this->getState();
	}
	for (int i = 0; i < ofHazardList.size(); i++)
		ofHazardList.at(i)->isVisible = this->getState();
}

void Game_Switch::setDoorState()
{
	for (int i = 0; i < this->getgameObjectContainer()->getObjects().size(); i++)
		if (dynamic_cast<Door*>(this->getgameObjectContainer()->getObjects().at(i)))
			if (dynamic_cast<Door*>(this->getgameObjectContainer()->getObjects().at(i))->getDoorId() == doorIndex)
				dynamic_cast<Door*>(this->getgameObjectContainer()->getObjects().at(i))->doAction();
}