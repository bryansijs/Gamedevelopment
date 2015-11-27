#pragma once
#include <string>
#include <vector>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>
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


	
	void setPosition(b2Vec2 position) { this->myBodyDef.position = position; };
	b2Vec2 getPosition() { return this->myBodyDef.position; };

	int getPositionX() { return this->myBodyDef.position.x; }
	int getPositionY() { return this->myBodyDef.position.y; }

	virtual void Update();
	virtual void doAction();
	virtual void setProperties(std::map<std::string, std::string>& properties);

	void setDrawBehaviour(DrawBehaviour* newDrawBehaviour);
	void SetMoveBehaviour(MoveBehaviour* moveBehaviour);
	void setMyBodydef(b2BodyDef body) { myBodyDef = body; };

	void move();

	void setDrawContainer(DrawContainer* newDrawContainer) {this->drawContainer = newDrawContainer	;}
	void setMoveContainer(MoveContainer* newMoveContainer) { this->moveContainer = newMoveContainer; }

	b2BodyDef getMyBodydef() { return myBodyDef; };

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


	bool isColliding(std::vector<Tile*> tiles, sf::Vector2f velocity);
	void createBoxStatic(b2World& World);
	void createBoxDynamic(b2World & World);

protected:
	b2BodyDef myBodyDef;
	b2PolygonShape Shape;
	b2Body* Body;
	b2FixtureDef boxFixtureDef;


};

