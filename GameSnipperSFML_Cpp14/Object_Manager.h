#pragma once

#include <unordered_map>
#include <vector>

#include <Box2D/Box2D.h>


#include "GameObject.h"

class Object_Manager
{
public:
	Object_Manager();

	void Add(std::string name, GameObject* entity);
	void Add(std::string name, std::string filename, bool dynamic);
	GameObject* Get(std::string name);

	bool Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);

	~Object_Manager();
private:
	std::unordered_map<std::string, GameObject*> entities;

	b2World* world;
};