#pragma once
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Tile.h"
#include "GameObject.h"
#include "TileSet.h"
#include "StartTile.h"
#include "EndTile.h"
#include "Time.h"
#include "Context.h"
#include "StateManager.h"
#include "LevelManager.h"

class Level
{
protected:
	sf::Sound music;
public:
	Level();
	~Level();
	Level(GameObjectContainer* gameObjectContainer);
	StartTile* start;
	EndTile* end;


	std::vector<GameObject*> game_objects;
	std::vector<Tile*> groundTiles;
	std::vector<Tile*> roofTiles;
	std::vector<TileSet*> tileSets;

	std::map<int, bool> hazardMap;

	void setHazardMap(std::map<int, bool> hazardMap)
	{
		this->hazardMap = hazardMap;
	}

	void updateViewPort(sf::Vector2i &worldPos);
	void MoveView(sf::View &view, sf::Window& window);

	void draw(sf::RenderWindow* window, sf::View* view);
	void drawRoof(sf::RenderWindow* window, sf::View* view);
	void update();

	void Start(GameObject* player, sf::Vector2u* size);
	void End(Context* context, StateManager* stateManager, LevelManager* levelManager, ScoreManager* scoreManager);
	void setLayerVisibility(int layerIndex, bool isVisible);
	bool getDoEvents() { return doEvents; }
	int getViewPortX() { return viewPortX; }
	int getViewPortY() { return viewPortY; }
	void setMusic(sf::Sound music) { this->music = music; }
	sf::Sound getMusic() { return music; }
	void pauseMusic(bool play) { if (!play)music.pause(); else music.play(); }


	void setGameObjects(std::vector<GameObject*>& game_objects) { this->game_objects.swap(game_objects); }
	void setTileSets(std::vector<TileSet*>& tileSets) { this->tileSets.swap(tileSets); }
	//void setTiles(std::vector<Tile*>& tiles) { this->tiles.swap(tiles);}


	std::vector<GameObject*> getGame_Objects() { return game_objects; }
	GameObject* getObject(int i) { return game_objects.at(i); }


	void setGameObjectContainer(GameObjectContainer* container)
	{
		this->gameObjectContainer = container;
	}

	GameObjectContainer* getGameObjectContainer() { return this->gameObjectContainer; }

	sf::Vector2f GetViewPortPosition();
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

	GameObjectContainer* gameObjectContainer;

};

