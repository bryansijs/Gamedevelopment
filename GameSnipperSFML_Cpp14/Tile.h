#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>

class Tile
{
public:
	Tile();
	~Tile();


	sf::Sprite sprite;
	int tileLayer;
	int x_Position;
	int y_Position;

	bool isHazard;
	bool hazardState;
	int hazardValue;
	int hazardIndex;
	int hazardType;
	int hazardLinkIndex;
	bool isEnemyCollidable;
	bool isCollidable;
	bool isVisible;

	b2BodyDef* bodyDef;
	b2BodyDef* enemyBodyDef;

};

