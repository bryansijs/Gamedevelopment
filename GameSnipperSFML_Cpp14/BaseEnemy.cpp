#include "stdafx.h"
#include "BaseEnemy.h"
#include "Time.h"
#include "KeyMapping.h"
#include "Player.h"
#include <Box2D\Dynamics\b2Body.h>
BaseEnemy::BaseEnemy()
{
}


BaseEnemy::~BaseEnemy()
{
}


BaseEnemy::BaseEnemy(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* gameObjectContainer) :Unit{ dContainer, img,mContainer, gameObjectContainer } {

}

void BaseEnemy::setProperties(std::map<std::string, std::string>& properties)
{
	int x, y, widht, height;
	x = std::stoi(properties["x"]);
	y = std::stoi(properties["y"]);
	widht = std::stoi(properties["width"]);
	height = std::stoi(properties["height"]);

	this->seeLenght = (properties.count("seeLenght")) ? std::stoi(properties["seeLenght"]) : 250;
	this->seeAngle = (properties.count("seeAngle")) ? std::stoi(properties["seeAngle"]) : 100;

	this->setPosition(x, y);
	this->setSize(widht, height);

	//Laten we een Line  of sight maken. 
	convex.setPointCount(3);
	convex.setFillColor(sf::Color(255, 129, 0, 128));




	myFixtureDef.shape = &chain;
	myFixtureDef.isSensor = true;

}

void BaseEnemy::Update()
{
	if (player == nullptr) {
		for (b2Body * b = world->GetBodyList(); b != NULL; b = b->GetNext()) {

			GameObject* wrapper = reinterpret_cast<GameObject*>(b->GetUserData());

			if (dynamic_cast<Player*>(wrapper))
			{

				player = dynamic_cast<Player*>(wrapper);
				break;
			}
		}
	}


	int b = this->getIndexY();
	b2Vec2 vec = this->getBody()->GetPosition();
	switch (b)
	{
	case 0: {
		vec.x = vec.x + this->getWidth() / 2;
		vec.y = vec.y + 15;
		vecB.y = vecA.y = vec.y + seeLenght;
		vecA.x = vec.x - seeAngle;
		vecB.x = vec.x + seeAngle;
	}	break;
	case 1: {
		vec.x = vec.x + this->getWidth() / 2;
		vec.y = vec.y + 15;
		vecB.x = vecA.x = vec.x - seeLenght;
		vecB.y = vec.y - seeAngle;
		vecA.y = vec.y + seeAngle;
	}	break;
	case 2: {
		vec.x = vec.x + this->getWidth() / 2;
		vec.y = vec.y + 15;
		vecB.x = vecA.x = vec.x + seeLenght;
		vecA.y = vec.y - seeAngle;
		vecB.y = vec.y + seeAngle;
	}	break;
	case 3: {
		vec.x = vec.x + this->getWidth() / 2;
		vec.y = vec.y + 15;
		vecB.y = vecA.y = vec.y - seeLenght;
		vecA.x = vec.x + seeAngle;
		vecB.x = vec.x - seeAngle;
	}	break;


	default:
		break;
	}

	vertices[0] = vec;
	vertices[1] = vecA;
	vertices[2] = vecB;
	chain.Set(this->vertices, 3);
	
	convex.setFillColor(sf::Color(255, 129, 0, 128));
	float playerx = player->getBody()->GetPosition().x + 16;
	float playery = player->getBody()->GetPosition().y + 16;
	
	
	
	if (playerx >= vecA.x && playerx <= vecB.x)
	{
		if (playery >= vec.y)
			convex.setFillColor(sf::Color(255, 0, 0, 128));
	}
	


	convex.setPoint(0, sf::Vector2f(vec.x, vec.y));
	convex.setPoint(1, sf::Vector2f(vecA.x, vecA.y) );
	convex.setPoint(2, sf::Vector2f(vecB.x, vecB.y));
}