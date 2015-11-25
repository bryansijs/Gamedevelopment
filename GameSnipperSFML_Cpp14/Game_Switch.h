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
	void setState()
	{
		this->isOn = !this->isOn;
		std::cout << "I switched the state state: " << isOn <<  " at location x y" << this->getPosition().x << " " << this->getPosition().y  << std::endl;
	}

	void setHazardState();
	void setDoorState();

	std::vector<Tile*> HazardList;
	std::vector<Tile*> ofHazardList;


public:
	Game_Switch();
	~Game_Switch();


	Game_Switch(DrawContainer* container);
	Game_Switch(DrawContainer* container, std::string img);
	Game_Switch(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height);

	Game_Switch(DrawContainer* container, GameObjectContainer *GameObjectContainer, std::string img, sf::Vector2f position, int widht, int height);

	Game_Switch(sf::Vector2f position, int widht, int height);
	Game_Switch(GameObjectContainer *useContainer,sf::Vector2f position, int widht, int height);
	virtual void setProperties(std::map<std::string, std::string>& properties);
	virtual void doAction();

	bool getState(){return this->isOn;	}

	virtual void Update();
	void setTiles(std::vector<Tile*>& tiles)
	{

		for (int i = 0; i < tiles.size(); i++)
		{
			if (tiles.at(i)->hazardIndex == hazardIndex)
			this->HazardList.push_back(tiles.at(i));

			if (tiles.at(i)->hazardLinkIndex == hazardIndex)
				ofHazardList.push_back(tiles.at(i));
		}
	}
	
};

