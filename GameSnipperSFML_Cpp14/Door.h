#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Tile.h"
class Door : public GameObject
{
	int doorId = 0;
	bool keyNeed = false;
	bool isOpen = false;
	bool keyUsed = false;
	bool switchNeed = false;
	bool shouldUpdate = false;
	bool useImage = false;
	int closedState = 3;
	int openState = 0; 

	void setOpen() {
		isOpen = !isOpen;

		if (!isOpen)
			this->setImageY(openState);
		else if (isOpen)
			this->setImageY(closedState);

		setDoorState();
	}

	std::vector<Tile*> DoorList;
	std::vector<Tile*> ofDoorList;
	void setDoorState();

public:
	Door();
	~Door();

	Door(DrawContainer* container);
	Door(DrawContainer* container, std::string img);
	Door(DrawContainer* container, std::string img, GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height);

	Door(GameObjectContainer* gameObjectContainer, sf::Vector2f position, int widht, int height);

	int getDoorId() { return doorId; };

	virtual void setProperties(std::map<std::string, std::string>& properties);
	virtual void doAction(Player* player);
	virtual void doAction();

	void setTiles(std::vector<Tile*>& tiles)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			if (tiles.at(i)->doorId == doorId)
				this->DoorList.push_back(tiles.at(i));
			if (tiles.at(i)->ofDoorId == doorId)
				this->ofDoorList.push_back(tiles.at(i));
		}
	}
};

