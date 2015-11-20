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
	GameObject* Create(std::map<std::string, std::string> properties, DrawContainer* container, UseContainer* uContainer);

private:
	GameObject* CreateSwitch(std::map<std::string, std::string>& properties, DrawContainer* container, UseContainer* uContainer);
	GameObject* CreateDoor(std::map<std::string, std::string>& properties, DrawContainer* container, UseContainer* uContainer);
	GameObject* CreateKeyHole(std::map<std::string, std::string>& properties, DrawContainer* container, UseContainer* uContainer);
	std::map<std::string, GameObject*(InteractiveFactory::*)(std::map<std::string, std::string>&, DrawContainer* container, UseContainer* uContainer)> possibleObjects = {
		{ "Switch", &InteractiveFactory::CreateSwitch },
		{ "Door", &InteractiveFactory::CreateDoor },
		{ "KeyHole", &InteractiveFactory::CreateKeyHole }, };

};

