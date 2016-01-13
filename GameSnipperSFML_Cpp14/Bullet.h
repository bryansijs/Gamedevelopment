#pragma once

#include "GameObject.h"
#include "GameContext.h"

class Bullet : public GameObject
{
public:
	Bullet(GameObjectContainer * gameObjectContainer, std::map<std::string, std::string>& properties, b2World * world, MoveContainer * moveContainer, DrawContainer * drawContainer, std::string texture);
	~Bullet();

	void SetContext(GameContext* context);
	void startContact(b2Fixture* fixture);
	void endContact(b2Fixture* fixture);


	void setVisible(bool visible) { this->isVisible = visible; }
	bool getVisible() { return this->isVisible; }
	void Remove() { this->Destroy(); }

private:
	GameContext* context;
	bool isVisible = false;
	int damage = 20;
};