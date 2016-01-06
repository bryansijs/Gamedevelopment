#pragma once
#include <SFML/Graphics/View.hpp>
#include "BaseItem.h"

class LevelManager;
class GameContext;
class AwesomiumHelper;

class HUD
{
public:
	HUD(GameContext* context);
	~HUD();

	bool Update();

	sf::View view;
	AwesomiumHelper* awesomium;
private:
	bool SetHealth(int value);
	bool SetItems(int keyAmount, std::map<BaseItem*, int> potions);
	bool SetWeapons();

	int health = -1;
	std::string items = "";

	GameContext* gamecontext;
};