#pragma once
#include "GameObject.h"
#include "Tile.h"

class Tile;
class Game_Switch : public GameObject
{

private:
	bool shouldUpdate = false;
	bool isOn;
	bool hazardOn;
	int hazardIndex = -1;
	int doorIndex = -1;

	bool needKey = false;
	bool usedKey = false;

	int ofState = 0;
	int onState = 0;
	int xOfIndex = -1;

	void setState()
	{
		this->isOn = !this->isOn;

		if(this->isOn)
			this->setImageY(onState);
		else
			this->setImageY(ofState);

	}

	void setHazardState();
	void setDoorState();

	std::vector<Tile*> HazardList;
	std::vector<Tile*> ofHazardList;


public:
	Game_Switch();
	~Game_Switch();

	Game_Switch(DrawContainer* container, GameObjectContainer *GameObjectContainer, std::string img,  std::map<std::string, std::string>& properties, std::vector<Tile*>& tileList, b2World* world);

	Game_Switch(GameObjectContainer *useContainer, std::map<std::string, std::string>& properties, std::vector<Tile*>& tileList, b2World* world);

	
	virtual void setProperties(std::map<std::string, std::string>& properties);
	virtual void doAction(Player* player);

	bool getState(){return this->isOn;	}

	virtual void Update();
	void setTiles(std::vector<Tile*>& tiles)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			if (tiles.at(i)->hazardIndex == hazardIndex)
				this->HazardList.push_back(tiles.at(i));
			if (tiles.at(i)->hazardLinkIndex == hazardIndex)
				this->ofHazardList.push_back(tiles.at(i));
		}
	}

	
};

