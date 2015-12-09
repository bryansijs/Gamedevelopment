#include "stdafx.h"
#include "EndTile.h"
#include <iostream>
#include "Player.h"
#include "WinState.h"

EndTile::EndTile(GameObjectContainer * gameObjectContainer, std::map<std::string, std::string>& properties, b2World * world)
{
	this->setProperties(properties);
	this->createBoxSenor(*world);
}

EndTile::~EndTile()
{
}

void EndTile::setProperties(std::map<std::string, std::string>& properties)
{
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);

	this->setPosition(x, y);
	this->setSize(widht, height);
}

void EndTile::doAction()
{
	sf::Image screenshot = context->window.capture();
	screenshot.saveToFile("./Resources/menuHTML/images/hold.png");

	WinState* winState = new WinState(context, stateManager, levelManager);
	stateManager->AddState(winState);
	stateManager->StartNextState();
}

void EndTile::startContact(b2Fixture * fixture)
{
	GameObject* pal = static_cast<Player*>(fixture->GetBody()->GetUserData());
	if (dynamic_cast<Player*> (pal)) {
		this->doAction();
	}

}

void EndTile::endContact(b2Fixture * fixture)
{
	
}

void EndTile::setContext(Context* context, StateManager* stateManager, LevelManager* levelManager)
{
	this->context = context;
	this->stateManager = stateManager;
	this->levelManager = levelManager;
}
