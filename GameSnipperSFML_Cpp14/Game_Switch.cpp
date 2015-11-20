#include "stdafx.h"
#include "Game_Switch.h"


Game_Switch::Game_Switch()
{
}


Game_Switch::~Game_Switch()
{
}


void Game_Switch::setProperties(std::map<std::string, std::string>& properties) {

}



Game_Switch::Game_Switch(DrawContainer* container) :GameObject{ container } {
};


Game_Switch::Game_Switch(DrawContainer* container, std::string img) :GameObject{ container, img } {
};


Game_Switch::Game_Switch(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height) :GameObject{ container, img } {
	this->setPosition(position);
	this->setSize(widht, height);
};



Game_Switch::Game_Switch(DrawContainer* container, UseContainer *useContainer, std::string img, sf::Vector2f position, int widht, int height) :GameObject{ container,useContainer, img } {
	this->setPosition(position);
	this->setSize(widht, height);
};



Game_Switch::Game_Switch(sf::Vector2f position, int widht, int height) :GameObject{  } {
	this->setPosition(position);
	this->setSize(widht, height);
};

Game_Switch::Game_Switch(UseContainer *useContainer, sf::Vector2f position, int widht, int height) :GameObject{useContainer} {
	this->setPosition(position);
	this->setSize(widht, height);
};

void Game_Switch::doAction()
{
	setState();
}