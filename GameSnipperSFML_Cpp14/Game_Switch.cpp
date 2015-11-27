#include "stdafx.h"
#include "Game_Switch.h"
#include "Tile.h"
#include <iterator> 
#include "GameObjectContainer.h"
#include "Door.h"
Game_Switch::Game_Switch()
{
}


Game_Switch::~Game_Switch()
{
}


void Game_Switch::setProperties(std::map<std::string, std::string>& properties) {

	this->hazardIndex = (properties.count("hazardIndex")) ? std::stoi(properties["hazardIndex"]) : -1;
	this->doorIndex = (properties.count("doorIndex")) ? std::stoi(properties["doorIndex"]) : -1;

	this->isOn = (properties.count("state")) ? std::stoi(properties["state"]) : 0;
	this->ofState = (properties.count("ofIndex")) ? std::stoi(properties["ofIndex"]) : 0;
	this->onState = (properties.count("onIndex")) ? std::stoi(properties["onIndex"]) : 2;
	this->setImageX((properties.count("xIndex")) ? std::stoi(properties["xIndex"]) : 0);

	if (this->isOn)
		this->setImageY(onState);
	else
		this->setImageY(ofState);

	this->shouldUpdate = true;
}



Game_Switch::Game_Switch(DrawContainer* container) :GameObject{ container } {
};


Game_Switch::Game_Switch(DrawContainer* container, std::string img) :GameObject{ container, img } {
};


Game_Switch::Game_Switch(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height) :GameObject{ container, "switches.png" } {
	this->setPosition(position);
	this->setSize(widht, height);
};



Game_Switch::Game_Switch(DrawContainer* container, GameObjectContainer *gameObjectContainer, std::string img, sf::Vector2f position, int widht, int height) :GameObject{ container,gameObjectContainer, img } {
	this->setPosition(position);
	this->setSize(widht, height);
};



Game_Switch::Game_Switch(sf::Vector2f position, int widht, int height) :GameObject{} {
	this->setPosition(position);
	this->setSize(widht, height);
};

Game_Switch::Game_Switch(GameObjectContainer *gameObjectContainer, sf::Vector2f position, int widht, int height) :GameObject{ gameObjectContainer } {
	this->setPosition(position);
	this->setSize(widht, height);
};

void Game_Switch::doAction()
{
	setState();
	shouldUpdate = true;
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