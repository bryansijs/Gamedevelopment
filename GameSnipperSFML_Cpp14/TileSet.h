#pragma once
#include <SFML\Graphics.hpp>

class TileSet
{
public:
	TileSet();
	~TileSet();

	int firstGrid;
	int imageHeight;
	int imageWidth;
	int tileAmount;
	int tileSize;
	sf::Texture tileImage;
};

