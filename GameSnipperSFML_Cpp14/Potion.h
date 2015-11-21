#pragma once
#include "GameObject.h"
class Potion : public GameObject
{
public:
	Potion();
	~Potion();

	Potion(DrawContainer* container);
	Potion(DrawContainer* container, std::string img);
	Potion(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height);

	virtual void setProperties(std::map<std::string, std::string>& properties);
};

