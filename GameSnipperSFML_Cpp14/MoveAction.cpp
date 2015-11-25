#include "stdafx.h"
#include "MoveAction.h"

#include "Player.h"
#include "Time.h"
#include "Tile.h"

#include <iostream>

MoveAction::MoveAction()
{
}

MoveAction::~MoveAction()
{
}

void MoveAction::Move(std::string direction, Player *player, std::vector<Tile>* tiles)
{
	//TODO wat er word hier per direct iets aangepast?
	//position van het object word een private die je later kunt opvragenmet een getter
	//Daarna zul je deze moeten zetten door middel van een setter!
	float temp = 0;
	if (direction == "move-up")
	{
		player->setImageY(3);
		temp = player->getPosition().y;
		temp += -velocity * Time::deltaTime;

		if (!player->isColliding(*tiles, player->getPosition().x, temp)) {
			float temp = player->getPositionY() + -velocity * Time::deltaTime;

			player->setPosition(sf::Vector2f(player->getPositionX(), temp));	
		}
	}
	if (direction == "move-down")
	{
		player->setImageY(0);
		temp = player->getPosition().y;
		temp += velocity * Time::deltaTime;
		if (!player->isColliding(*tiles, player->getPosition().x, temp)) {

			float temp = player->getPositionY() + velocity * Time::deltaTime;

			player->setPosition(sf::Vector2f(player->getPositionX(), temp));
		}
	}
	if (direction == "move-left")
	{
		player->setImageY(1);
		temp = player->getPosition().x;
		temp += -velocity * Time::deltaTime;
		if (!player->isColliding(*tiles, temp, player->getPosition().y)) {
	
			float temp = player->getPositionX() + -velocity * Time::deltaTime;

			player->setPosition(sf::Vector2f(temp, player->getPositionY()));

		}
	}
	if (direction == "move-right")
	{
		player->setImageY(2);
		temp = player->getPosition().x;
		temp += velocity * Time::deltaTime;
		if (!player->isColliding(*tiles, temp, player->getPosition().y)) {
			float temp = player->getPositionX() + velocity * Time::deltaTime;
			player->setPosition(sf::Vector2f(temp, player->getPositionY()));
		}
	}
}