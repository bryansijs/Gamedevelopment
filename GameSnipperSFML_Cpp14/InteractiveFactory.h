#pragma once
#include <map>
#include <string>
#include  <memory>
#include "GameObject.h"


class GameObject;

class InteractiveFactory
{
public:
	InteractiveFactory();
	~InteractiveFactory();
	GameObject* Create(std::map<std::string, std::string> properties, DrawContainer* container);

private:
	GameObject* CreateSwitch(std::map<std::string, std::string>& properties, DrawContainer* container);
	GameObject* CreateDoor(std::map<std::string, std::string>& properties, DrawContainer* container);
	GameObject* CreateKeyHole(std::map<std::string, std::string>& properties, DrawContainer* container);
	std::map<std::string, GameObject*(InteractiveFactory::*)(std::map<std::string, std::string>&, DrawContainer* container)> possibleObjects = {
		{ "Switch", &InteractiveFactory::CreateSwitch },
		{ "Door", &InteractiveFactory::CreateDoor },
		{ "KeyHole", &InteractiveFactory::CreateKeyHole }, };

};

