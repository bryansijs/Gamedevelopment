#pragma once
#include "GameObject.h"
class Game_Switch : public GameObject
{

private:
	bool isOn;

	void setState()
	{
		this->isOn = !this->isOn;
		std::cout << "I switched the state state: " << isOn << std::endl;
	}


public:
	Game_Switch();
	~Game_Switch();


	Game_Switch(DrawContainer* container);
	Game_Switch(DrawContainer* container, std::string img);
	Game_Switch(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height);

	Game_Switch(DrawContainer* container,UseContainer *useContainer, std::string img, sf::Vector2f position, int widht, int height);

	Game_Switch(sf::Vector2f position, int widht, int height);
	Game_Switch(UseContainer *useContainer,sf::Vector2f position, int widht, int height);
	virtual void setProperties(std::map<std::string, std::string>& properties);
	virtual void doAction();



	bool getState()
	{
		return this->isOn;
	}
};

