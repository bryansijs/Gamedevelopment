#pragma once
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>
#include "Tile.h"
#include "GameObject.h"
#include "GameObject.h"
#include "TileSet.h"
#include "StartTile.h"

class Level
{
public:
	Level();
	~Level();

	std::vector<GameObject*> game_objects;
	std::vector<Tile> tiles;
	std::vector<TileSet> tileSets;


	void updateViewPort(sf::Vector2i &worldPos);
	void MoveView(sf::View &view);

	void draw(sf::RenderWindow* window, sf::View* view);
	void update();

	void setHazardState(int hazardIndex, bool hazardState);
	void Start(GameObject* player, sf::Vector2u* size);
	void setLayerVisibility(int layerIndex, bool isVisible);
	bool getDoEvents() { return doEvents; }
	int getViewPortX() { return viewPortX; }
	int getViewPortY() { return viewPortY; }
	

	void setGameObjects(std::vector<GameObject*>& game_objects) { this->game_objects.swap(game_objects); }
	void setTileSets(std::vector<TileSet>& tileSets) { this->tileSets.swap(tileSets); }
	void setTiles(std::vector<Tile>& tiles) { this->tiles.swap(tiles);}


	std::vector<GameObject*> getGame_Objects() { return game_objects; }
	GameObject* getObject(int i) { return game_objects.at(i); }

	/*std::string getObjectType(int i)
	{
		if (dynamic_cast<t_Enemy*> (getObject(i)))
			return "Enemy";
		if (dynamic_cast<t_Door*> (getObject(i)))
			return "Door";
		if (dynamic_cast<t_Switch*> (getObject(i)))
			return "Switch";
		if (dynamic_cast<t_EndTile*> (getObject(i)))
			return "EndTile";
		if (dynamic_cast<t_WarpTile*> (getObject(i)))
			return "WarpTile";
		if (dynamic_cast<t_StartTile*> (getObject(i)))
			return "StartTile";

		return "Object";
	}*/

private:
	bool doEvents = true;
	bool moveDown = true;
	bool moveRight = true;

	int t_value = 0;
	int t_max = 0;

	int r_value = 0;
	int r_max = 0;

	int viewPortX = 0;
	int viewPortY = 0;

};

