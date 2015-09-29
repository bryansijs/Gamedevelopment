#include "stdafx.h"
#include "Object_Manager.h"

Object_Manager::Object_Manager()
{
	this->world = new b2World(b2Vec2(0, -10));
}

void Object_Manager::Add(std::string name, GameObject* entity)
{
	std::unordered_map<std::string, GameObject*>::const_iterator found = this->entities.find(name);
	while (found != this->entities.end())
	{
		name += "0";
		found = this->entities.find(name);
	}
	this->entities.insert(std::make_pair(name, entity));
}

void Object_Manager::Add(std::string name, std::string filename, bool dynamic)
{
	std::unordered_map<std::string, GameObject*>::const_iterator found = this->entities.find(name);
	while (found != this->entities.end())
	{
		name += "0";
		found = this->entities.find(name);
	}
	GameObject* entity = new GameObject(this->world);
	entity->Load(filename, dynamic);
	this->entities.insert(std::make_pair(name, entity));
}

GameObject* Object_Manager::Get(std::string name)
{
	std::unordered_map<std::string, GameObject*>::const_iterator found = this->entities.find(name);

	if (found == this->entities.end())
	{
		return NULL;
	}
	else
	{
		return found->second;
	}
}

bool Object_Manager::Update(sf::RenderWindow* window)
{
	std::vector<std::string> toRemove;

	this->world->Step(1.0f / 60.0f, 6, 2);

	for (auto& iterator : this->entities)
	{
		switch (iterator.second->Active())
		{
		case 0:
			toRemove.push_back(iterator.first);
			break;
		default:
			if (!iterator.second->Update(window))
			{
				return false;
			}
			break;
		}
	}

	for (auto& iterator : toRemove)
	{
		std::unordered_map<std::string, GameObject*>::const_iterator found = this->entities.find(iterator);

		if (found != this->entities.end())
		{
			delete found->second;
			this->entities.erase(iterator);
		}
	}
	toRemove.clear();

	return true;
}

void Object_Manager::Render(sf::RenderWindow* window)
{
	for (auto& iterator : this->entities)
	{
		window->draw(*iterator.second);
	}
}

Object_Manager::~Object_Manager()
{
	for (auto& iterator : this->entities)
	{
		delete iterator.second;
	}
	this->entities.clear();
	delete this->world;
}