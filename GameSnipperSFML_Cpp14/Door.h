#pragma once
#include "GameObject.h"
#include "Player.h"

class Door : public GameObject
{
	int doorId = 0;
	bool keyNeed = false;
	bool isOpen = false;
	bool switchNeed = false;
	bool shouldUpdate = false;
	
	int ofState = 0;
	int onState = 0; 

	void setOpen() {
		isOpen = !isOpen;
		if (!isOpen)
			this->setImageY(ofState);
		else if (isOpen)
			this->setImageY(onState);
	}

public:
	Door();
	~Door();

	Door(DrawContainer* container);
	Door(DrawContainer* container, std::string img);
	Door(DrawContainer* container, std::string img, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height);

	int getDoorId() { return doorId; };

	virtual void setProperties(std::map<std::string, std::string>& properties);
	virtual void doAction(Player* player);
	virtual void doAction();
};

