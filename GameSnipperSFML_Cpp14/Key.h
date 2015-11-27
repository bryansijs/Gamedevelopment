#pragma once
#include "GameObject.h"
class Key : public GameObject
{
public:
	Key();
	~Key();

	Key(DrawContainer* container);
	Key(DrawContainer* container, std::string img);
	Key(DrawContainer* container, std::string img,GameObjectContainer* gameObjectContainer, b2Vec2 position, int widht, int height);

	virtual void setProperties(std::map<std::string, std::string>& properties);
};

