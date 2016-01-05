#pragma once
#include <SFML/Graphics/View.hpp>

class LevelManager;
class GameContext;
class AwesomiumHelper;

class HUD
{
public:
	HUD(GameContext* context, LevelManager* levelmanager);
	~HUD();

	bool Update();

	sf::View view;
	AwesomiumHelper* awesomium;
private:
	bool SetHealth(int value);
	bool SetLevel(int value);

	int health = -1;
	int level = -1;

	GameContext* gamecontext;
	LevelManager* levelmanager;
};