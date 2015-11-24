#pragma once
#include "GameObject.h"
class Game_Switch : public GameObject
{

private:
	bool isOn;
	int hazardIndex = -1;
	int doorIndex = -1;
	void setState()
	{
		this->isOn = !this->isOn;
		std::cout << "I switched the state state: " << isOn <<  " at location x y" << this->getPosition().x << " " << this->getPosition().y  << std::endl;
	}

	void setHazardState(std::vector<Tile>& tiles, std::map<int, bool>& hazardMap);
	void setDoorState(int doorIndex);


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

	virtual void Update(std::vector<Tile>& tiles, std::map<int, bool>& hazardMap);
	
};

