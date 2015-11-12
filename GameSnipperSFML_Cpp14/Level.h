#pragma once
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Tile.h"
#include "GameObject.h"
#include "TileSet.h"
#include "StartTile.h"
#include "Time.h"

class Level
{
protected:
	sf::Sound music;
public:
	Level();
	~Level();

	std::vector<	GameObject*> game_objects;
	std::vector<Tile> tiles;
	std::vector<TileSet> tileSets;


	void updateViewPort(sf::Vector2i &worldPos);
	void MoveView(sf::View &view, sf::Window& window);

	void draw(sf::RenderWindow* window, sf::View* view);
	void update();

	void setHazardState(int hazardIndex, bool hazardState);
	void Start(GameObject* player, sf::Vector2u* size);
	void setLayerVisibility(int layerIndex, bool isVisible);
	bool getDoEvents() { return doEvents; }
	int getViewPortX() { return viewPortX; }
	int getViewPortY() { return viewPortY; }
	void setMusic(sf::Sound music) { this->music = music; }
	

	void setGameObjects(std::vector<GameObject*>& game_objects) { this->game_objects.swap(game_objects); }
	void setTileSets(std::vector<TileSet>& tileSets) { this->tileSets.swap(tileSets); }
	void setTiles(std::vector<Tile>& tiles) { this->tiles.swap(tiles);}


	std::vector<	GameObject*> getGame_Objects() { return game_objects; }
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

	float t_value = 0.0f;
	float t_max = 0.0f;

	float r_value = 0.0f;
	float r_max = 0.0f;

	int viewPortX = 0;
	int viewPortY = 0;

};

