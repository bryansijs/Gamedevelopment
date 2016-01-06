#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>
#include "GameObject.h"

class GameObject;

class Tile : public GameObject
{
public:
	Tile();
	~Tile();


	sf::Sprite sprite;
	int tileLayer;
	//int x_Position;
	//int y_Position;

	bool isHazard;
	bool hazardState;
	int hazardValue;
	int hazardIndex;
	int hazardType;
	int hazardLinkIndex;
	bool isEnemyCollidable;
	bool isCollidable;
	bool isVisible;
	bool topTile = false;

	//b2BodyDef* bodyDef;
	//b2BodyDef* enemyBodyDef;
	void createStaticBody(b2World& world);

	float getPositionX() { return this->myBodyDef.position.x; }
	float getPositionY() { return this->myBodyDef.position.y; }

	void setPositionX(float x) { this->myBodyDef.position.x = x; };
	void setPositionY(float y) { this->myBodyDef.position.y = y; };

	b2Body* getBody() { return Body; };
	b2BodyDef getBodyDef() { return myBodyDef; };
	
	int doorId;
	int ofDoorId;

protected:
	b2BodyDef myBodyDef;
	b2PolygonShape Shape;
	b2Body* Body;
	b2FixtureDef boxFixtureDef;


	

};

