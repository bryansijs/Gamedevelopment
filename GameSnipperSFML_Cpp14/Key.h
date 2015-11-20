#pragma once
#include "GameObject.h"
class Key : public GameObject
{
public:
	Key();
	~Key();

	Key(DrawContainer* container);
	Key(DrawContainer* container, std::string img);
	Key(DrawContainer* container, std::string img, sf::Vector2f position, int widht, int height);

	virtual void setProperties(std::map<std::string, std::string>& properties);
};

