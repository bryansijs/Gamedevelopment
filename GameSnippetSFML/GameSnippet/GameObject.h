#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <Box2D/Box2D.h>

class GameObject : public sf::Sprite
{
public:
	sf::Vector2f velocity;

	GameObject(b2World* world);

	virtual void Load(std::string filename, bool dynamic);

	virtual bool Update(sf::RenderWindow* window);

	bool CheckCollision(GameObject* gameObject);

	virtual void Collision(GameObject* gameObject);

	void setSounds(std::string fileName);

	void Handle();
	void MoveUnit(float x, float y);

	int GroupID();

	int Active();

	void Destroy();
	b2Body* body;

	~GameObject();
protected:
	int active;
	int groupId;
	b2World* world;
	b2BodyDef* bodyDef;
	b2PolygonShape* shape;
	b2FixtureDef* fixtureDef;
	sf::SoundBuffer sbuffer;
	sf::Sound sfx;
private:
	sf::Texture* texture;
};