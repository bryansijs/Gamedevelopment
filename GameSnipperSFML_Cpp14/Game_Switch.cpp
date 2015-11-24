#include "stdafx.h"
#include "Game_Switch.h"

#include "Tile.h"

Game_Switch::Game_Switch()
{
}


Game_Switch::~Game_Switch()
{
}


void Game_Switch::setProperties(std::map<std::string, std::string>& properties) {
	
	hazardIndex = (properties.count("hazardIndex")) ? std::stoi(properties["hazardIndex"]) : -1;
	doorIndex = (properties.count("doorIndex")) ? std::stoi(properties["doorIndex"]) : -1;
}



Game_Switch::Game_Switch(DrawContainer* container) :GameObject{ container } {
};


Game_Switch::Game_Switch(DrawContainer* container, std::string img) :GameObject{ container, img } {
};


Game_Switch::Game_Switch(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height) :GameObject{ container, img } {
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
}


void Game_Switch::Update(std::vector<Tile>& tiles, std::map<int, bool>& hazardMap)
{
	if (hazardIndex >= 0) {
		setHazardState(tiles, hazardMap);
	}
}

void Game_Switch::setHazardState(std::vector<Tile>& tiles, std::map<int, bool>& hazardMap)
{
	auto search = hazardMap.find(hazardIndex);
	if (search != hazardMap.end()) {

		if (search->second != this->getState())
		{
			search->second = this->getState();
			for (int i = 0; i < tiles.size(); i++)
			{
				if (tiles.at(i).hazardIndex == hazardIndex)
				{
					tiles.at(i).hazardState = !this->getState();
					tiles.at(i).isVisible = !this->getState();
				}

				if (tiles.at(i).hazardLinkIndex == hazardIndex)
					tiles.at(i).isVisible = this->getState();
			}
		}
	}

}

