#pragma once
#include <map>
#include <string>
#include  <memory>
#include "GameObject.h"

class GameObject;

class ItemFactory
{
public:
	ItemFactory();
	~ItemFactory();

	GameObject* Create(std::map<std::string, std::string> properties, DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world);
private:
	GameObject* CreatePotion(std::map<std::string, std::string>& properties, DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world);
	GameObject* CreateAmmo(std::map<std::string, std::string>& properties, DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer, b2World* world);
	GameObject* CreateKey(std::map<std::string, std::string>& properties, DrawContainer* drawContainer, MoveContainer* moveContainer, GameObjectContainer* gameObjectContainer,b2World* world);

	std::map<std::string, GameObject*(ItemFactory::*)(std::map<std::string, std::string>&, DrawContainer*, MoveContainer*, GameObjectContainer*, b2World* )> possibleObjects = {
		{ "Potion", &ItemFactory::CreatePotion },
		{ "Ammo", &ItemFactory::CreateAmmo },
		{ "Key", &ItemFactory::CreateKey }
	};
};


