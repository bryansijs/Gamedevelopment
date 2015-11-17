#pragma once
#include <map>
#include <iostream>
#include <string>
#include  <memory>


class GameObject;

class InteractiveFactory
{
public:
	InteractiveFactory();
	~InteractiveFactory();
	/*

	GameObject* Create(std::map<std::string, std::string> properties);

	std::map<std::string, GameObject*(InteractiveFactory::*)(std::map<std::string, std::string>)> possibleTiles = {
		{ "Switch", &InteractiveFactory::CreateSwitch },
		{ "Door", &InteractiveFactory::CreateDoor },
		{ "KeyHole", &InteractiveFactory::CreateKeyHole }, };


private:
	GameObject* CreateSwitch(std::map<std::string, std::string> properties);
	GameObject* CreateDoor(std::map<std::string, std::string>properties);
	GameObject* CreateKeyHole(std::map<std::string, std::string> properties);*/
};

