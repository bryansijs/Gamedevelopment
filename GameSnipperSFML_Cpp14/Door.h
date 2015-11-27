#pragma once
#include "GameObject.h"

class Door : public GameObject
{
	int doorId=0;
public:
	Door();
	~Door();

	Door(DrawContainer* container);
	Door(DrawContainer* container, std::string img);
	Door(DrawContainer* container, std::string img, b2Vec2 position, int widht, int height);
	int getDoorId() { return doorId; };
	virtual void setProperties(std::map<std::string, std::string>& properties);
};

