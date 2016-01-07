#pragma once
#include "GameObject.h"

class Discovery : public GameObject
{
public:
	Discovery(DrawContainer* container, GameObjectContainer* gameObjectContainer, std::map<std::string, std::string>& properties, std::vector<Tile*>& tiles, b2World* world);
	~Discovery();

	virtual void setProperties(std::map<std::string, std::string>& properties);
	virtual void doAction();

	virtual void startContact(b2Fixture* fixture);
	virtual void endContact(b2Fixture* fixture);

};

