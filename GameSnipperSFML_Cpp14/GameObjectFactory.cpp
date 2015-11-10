#include "stdafx.h"
#include "GameObjectFactory.h"

#include "StartTile.h"
GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::GameObjectFactory(DrawContainer *drawContainer)
{
	this->drawContainer = drawContainer;
}

GameObjectFactory::~GameObjectFactory()
{
}

enum string_code {
	s_Enemy,
	s_Switch,
	s_Door,
	s_StartTile,
	s_EndTile,
	s_WarpTile

};

string_code hashit(std::string const& inString) {
	if (inString == "Enemy") return s_Enemy;
	if (inString == "Switch") return s_Switch;
	if (inString == "Door") return s_Door;
	if (inString == "StartTile") return s_StartTile;
	if (inString == "EndTile") return s_EndTile;
	if (inString == "WarpTile") return s_WarpTile;
}




GameObject* GameObjectFactory::Create(Json::Value root) {
	GameObject* object = nullptr;
	//object = std::unique_ptr<EndTile>();
	std::string imgurl = root["properties"]["image"].asString();
	int x, y, widht, height;

	switch (hashit(root["type"].asString()))
	{

	case s_Enemy: {
		object = new GameObject(drawContainer, imgurl);
		break;
	}

	case s_StartTile:
	{
		object = new StartTile();
		break;
	}


	}

	if (object != nullptr) {

		x = root["x"].asInt();
		y = root["y"].asInt();
		widht = root["width"].asInt();
		height = root["height"].asInt();
		object->setPosition(sf::Vector2f(x, y));
		object->setSize(widht, height);

	}

	return object;
	//case s_EndTile:
	//{
	//	/*	EndTile * endTile = new EndTile();
	//		x = val["x"].asInt();
	//		y = val["y"].asInt();
	//		widht = val["width"].asInt();
	//		height = val["height"].asInt();

	//		endTile->setSize(widht, height);*/

	//	break;
	//}

	//case s_WarpTile: {
	//	/*	WarpTile *warpTile = new WarpTile();
	//		x = val["x"].asInt();
	//		y = val["y"].asInt();
	//		widht = val["width"].asInt();
	//		height = val["height"].asInt();
	//		warpTile->setPosition(sf::Vector2f(x, y));
	//		warpTile->setSize(widht, height);*/

	//	break;
	//}



	//case s_StartTile:
	//{
	//	/*	StartTile *startTile = new StartTile();
	//		x = val["x"].asInt();
	//		y = val["y"].asInt();
	//		widht = val["width"].asInt();
	//		height = val["height"].asInt();
	//		startTile->setPosition(sf::Vector2f(x, y));*/

	//	break;
	//}

	//case s_Switch:
	//{
	//	/*	Game_Switch *_Switch = new Game_Switch();
	//		x = val["x"].asInt();
	//		y = val["y"].asInt();
	//		widht = val["width"].asInt();
	//		height = val["height"].asInt();
	//		_Switch->setPosition(sf::Vector2f(x, y));
	//		_Switch->setSize(widht, height);*/

	//	break;
	//}

	//case s_Door:
	//{
	//	/*	Door *door = new Door();
	//		x = val["x"].asInt();
	//		y = val["y"].asInt();
	//		widht = val["width"].asInt();
	//		height = val["height"].asInt();
	//		door->setPosition(sf::Vector2f(x, y));
	//		door->setSize(widht, height);
	//		*/

	//}



	//default:
	//{
	//	/*	std::string imgurl = val["properties"]["image"].asString();

	//		GameObject* Object = nullptr;
	//		if (imgurl == "")
	//		{
	//			Object = new GameObject();
	//		}
	//		else
	//		{
	//			Object = new GameObject(drawContainer, imgurl);
	//		}

	//		x = val["x"].asInt();
	//		y = val["y"].asInt();
	//		widht = val["width"].asInt();
	//		height = val["height"].asInt();
	//		Object->setPosition(sf::Vector2f(x, y));
	//		Object->setSize(widht, height);
	//		break;*/
	//}



	//}

}