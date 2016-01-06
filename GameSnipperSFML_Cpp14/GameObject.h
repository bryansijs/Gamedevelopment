#pragma once
#include <string>
#include <vector>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

class Player;
class DrawContainer;
class GameObjectContainer;
class MoveContainer;
class DrawBehaviour;
class MoveBehaviour;

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

	int visibleId;
	int animationStates;
public:
	GameObject(DrawContainer *drawContainer, std::string textureUrl);
	GameObject();
	GameObject(GameObjectContainer *useContainer);
	GameObject(GameObjectContainer *gameObjectContainer, MoveContainer *moveContainer, std::string textureUrl);
	GameObject(DrawContainer *drawContainer, GameObjectContainer *gameObjectContainer, std::string textureUrl);
	GameObject(DrawContainer *drawContainer, GameObjectContainer *gameObjectContainer, MoveContainer *moveContainer, std::string textureUrl);
	GameObject(DrawContainer *drawContainer);
	~GameObject();

	void SetAnimationStates(int states) { animationStates = states; };
	int GetAnimationStates() { return animationStates; };
	
	void setPosition(float x, float y) { this->myBodyDef.position.Set(x, y); };
	b2Vec2 getPosition() { return this->myBodyDef.position; };

	int getPositionX() { return this->myBodyDef.position.x; }
	int getPositionY() { return this->myBodyDef.position.y; }

	virtual void Update();
	virtual void doAction(Player* player);
	virtual void setProperties(std::map<std::string, std::string>& properties);

	void setDrawBehaviour(DrawBehaviour* newDrawBehaviour);
	void SetMoveBehaviour(MoveBehaviour* moveBehaviour);
	void setMyBodydef(b2BodyDef body) { myBodyDef = body; };

	void setDrawContainer(DrawContainer* newDrawContainer) {this->drawContainer = newDrawContainer	;}
	void setMoveContainer(MoveContainer* newMoveContainer) { this->moveContainer = newMoveContainer; }
	void setVisibleId(int id) { this->visibleId = id; }

	b2BodyDef getMyBodydef() { return myBodyDef; };
	b2Body* getBody() { return Body; };
	DrawContainer* getDrawContainer() { return this->drawContainer; }
	MoveContainer* getMoveContainer() { return this->moveContainer; }
	GameObjectContainer* getgameObjectContainer() { return this->gameObjectContainer; }
	int getVisibleId() { return this->visibleId; }

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

	int getIndexY() { return yIndex; }
	int getIndexX() { return xIndex; }
	int getImageY() { return yIndex * height; }
	int getImageX() { return xIndex * width; }
	int getHeight() { return height; }
	int getWidth() { return width; }
	bool isCollidable = false;
	void setSize(int width, int height)
	{
		this->width = width;
		this->height = height;
		imageRect.height = height;
		imageRect.width = width;
	}


	void createBoxStatic(b2World& World);
	void createBoxDynamic(b2World & World);
	void createBoxDynamicForPlayers(b2World & World);
	void createBoxSenor(b2World & World);

	virtual void startContact(b2Fixture* fixture);
	virtual void endContact(b2Fixture* fixture);

	bool isFlaggedForDelete = false;

	b2World* theWorld() { return this->world; }
protected:
	b2BodyDef myBodyDef;
	b2PolygonShape Shape;
	b2Body* Body;
	b2FixtureDef boxFixtureDef;
	b2World* world;

	void Destroy();
};

