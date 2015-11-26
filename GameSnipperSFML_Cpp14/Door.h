#pragma once
#include "GameObject.h"

class Door : public GameObject
{
	int doorId=0;
	bool keyNeed = false;
	bool isOpen = false;


public:
	Door();
	~Door();

	Door(DrawContainer* container);
	Door(DrawContainer* container, std::string img);
	Door(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height);
	int getDoorId() { return doorId; };
	virtual void setProperties(std::map<std::string, std::string>& properties);

	void setOpen() { isOpen = true; }
};

