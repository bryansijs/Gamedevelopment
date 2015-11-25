#pragma once
#include <string>
#include <vector>
#include <SFML\Graphics.hpp>
#include <iostream>

class DrawContainer;
class MoveContainer;
class DrawBehaviour;
class MoveBehaviour;
class GameObjectContainer;
class Tile;

class GameObject
{

private:
	std::string name;
	std::string type;

	GameObjectContainer*  gameObjectContainer;
	DrawContainer* drawContainer;
	MoveContainer* moveContainer;
	DrawBehaviour* drawBehaviour;
	MoveBehaviour* moveBehaviour;


	sf::Vector2f position;
	int xIndex = 0;
	int yIndex = 0;
	int width = 0;
	int height = 0;


public:
	GameObject(DrawContainer *drawContainer, std::string textureUrl);
	GameObject(DrawContainer *drawContainer);
	GameObject();
	GameObject(GameObjectContainer *useContainer);
	GameObject::GameObject(DrawContainer *drawContainer, GameObjectContainer *gameObjectContainer, std::string textureUrl);
	~GameObject();


	
	void setPosition(sf::Vector2f position) { this->position = position; };
	sf::Vector2f getPosition() { return position; }

	int getPositionX() { return position.x; }
	int getPositionY() { return position.y; }

	virtual void Update();
	virtual void doAction();
	virtual void setProperties(std::map<std::string, std::string>& properties);

	void setDrawBehaviour(DrawBehaviour* newDrawBehaviour);
	void SetMoveBehaviour(MoveBehaviour* moveBehaviour);

	void setDrawContainer(DrawContainer* newDrawContainer) {this->drawContainer = newDrawContainer	;}
	void setMoveContainer(MoveContainer* newMoveContainer) { this->moveContainer = newMoveContainer; }


	DrawContainer* getDrawContainer() { return this->drawContainer; }
	MoveContainer* getMoveContainer() { return this->moveContainer; }
	GameObjectContainer* getgameObjectContainer() { return this->gameObjectContainer; }


	DrawBehaviour* getDrawBehaviour() { return this->drawBehaviour; }
	MoveBehaviour* getMoveBehaviour() { return this->moveBehaviour; }

	void setUseContainer(GameObjectContainer* gameObjectContainer) { this->gameObjectContainer = gameObjectContainer; }
	sf::IntRect imageRect =  sf::IntRect(0, 0, 0, 0);

	void setImageX(int x)
	{
		this->xIndex = x;
	}

	void setImageY(int y)
	{
		this->yIndex = y;
	}

	int getImageY() { return yIndex * height; }
	int getImageX() { return xIndex * width; }
	int getHeight() { return height; }
	int getWidth() { return width; }

	void setSize(int width, int height)
	{
		this->width = width;
		this->height = height;
		imageRect.height = height;
		imageRect.width = width;
	}

	bool isColliding(std::vector<Tile> tiles, float newX, float newY);
};

