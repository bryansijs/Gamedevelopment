#include "stdafx.h"
#include "Level.h"
#include "Game_Switch.h"

Level::Level()
{
}

Level::Level(GameObjectContainer* gameObjectContainer)
{
	this->gameObjectContainer = gameObjectContainer;
}


Level::~Level()
{
}

void  Level::updateViewPort(sf::Vector2i &worldPos)
{
	//updateVP
	if (worldPos.y > 640)
	{
		doEvents = false;
		t_max += 640;
		moveDown = true;
	}

	if (worldPos.y < 0)
	{
		doEvents = false;
		t_max -= 640;
		moveDown = false;
	}

	if (worldPos.x > 960)
	{
		doEvents = false;
		r_max += 960;
		moveRight = true;
	}

	if (worldPos.x < 0)
	{
		doEvents = false;
		r_max -= 960;
		moveRight = false;
	}
}

void Level::MoveView(sf::View& view, sf::Window& window)
{
	float time = 600.0f * Time::deltaTime;
	if (moveDown)
	{
		if (t_value < t_max)
		{
			t_value += time;
			view.move(0, +time);
			if (t_value > t_max)
			{
				view.move(0, -(t_value - t_max));
				t_value = t_max;
			}
		}
	}
	else
	{
		if (t_value > t_max)
		{
			t_value -= time;
			view.move(0, -time);
			if (t_value < t_max)
			{
				view.move(0, -(t_value - t_max));
				t_value = t_max;
			}
		}
	}

	if (moveRight)
	{
		if (r_value < r_max)
		{
			r_value += time;
			view.move(time, 0);
			if (r_value > r_max)
			{
				view.move(-(r_value - r_max), 0);
				r_value = r_max;
			}
		}
	}
	else
	{
		if (r_value > r_max)
		{
			r_value -= time;
			view.move(-time, 0);
			if (r_value < r_max)
			{
				view.move(-(r_value - r_max), 0);
				r_value = r_max;
			}
		}
	}

	if (t_value == t_max && r_value == r_max)
	{
		doEvents = true;
	}
}

void Level::update()
{

	for (size_t i = 0; i < getGame_Objects().size(); i++)
	{
		if (dynamic_cast<Game_Switch*>(getObject(i)))
		{
			dynamic_cast<Game_Switch*>(getObject(i))->Update();
		}
	}
}

void Level::draw(sf::RenderWindow* window, sf::View* view)
{
	for (size_t i = 0; i < tiles.size(); i++)
		if (tiles.at(i)->isVisible)
			window->draw(tiles.at(i)->sprite);
	MoveView(*view, *window);
}

void Level::setLayerVisibility(int layerIndex, bool isVisible)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles.at(i)->tileLayer == layerIndex)
			tiles.at(i)->isVisible = isVisible;
	}
}

void Level::Start(GameObject* player, sf::Vector2u* size)
{
	StartTile* start = nullptr;

	for (size_t i = 0; i < game_objects.size(); i++)
	{
		if (dynamic_cast<StartTile*> (getObject(i))) {
			start = dynamic_cast<StartTile*> (getObject(i));
			break;
		}
	}

	if (start == nullptr)
	{
		start = new StartTile(gameObjectContainer);
		start->setPosition(sf::Vector2f(25, 25));
	}

	int map_yLocation = start->getPosition().y / size->y;
	int map_xLocation = start->getPosition().x / size->x;
	viewPortY = (map_yLocation * size->y);
	viewPortX = (map_xLocation * size->x);

	player->setPosition(sf::Vector2f(start->getPosition().x, start->getPosition().y));
	music.setLoop(true);
	music.play();
}