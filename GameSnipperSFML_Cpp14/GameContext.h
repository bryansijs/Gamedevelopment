#pragma once

#include "Context.h"

#include "Player.h"
#include "PlayerInput.h"
#include "PlayerActions.h"

#include "KeyMappingImporter.h"

#include "LevelImporter.h"
#include "Level.h"

#include "PauseMenu.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

class Context;
class MoveContainer;
class DrawContainer;
class GameObjectContainer;
class CollisionListener;

class GameContext
{
public: 
	GameContext(Context* context);
	~GameContext();

	Context* context;

	MoveContainer* moveContainer;
	DrawContainer* drawContainer;
	GameObjectContainer *useContainer;

	Player* player;
	PlayerInput playerInput;
	PlayerActions* playerActions;
	KeyMappingImporter keyMappingImporter;

	LevelImporter* levelImporter;
	Level* level;

	sf::Clock deltaClock;
	sf::Event event;
	sf::View view;

	void setMenuPosition();
	PauseMenu* pauze = new PauseMenu{ 321,395 };

	b2World* world;
	CollisionListener* collisionListener;

	Awesomium::WebView* webView;
	Awesomium::WebCore* web_core;
	Awesomium::BitmapSurface* surface;

	sf::Texture texture;
	sf::Uint8* pixels;

	bool loading;
};

