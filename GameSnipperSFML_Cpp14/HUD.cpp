#include "stdafx.h"
#include "HUD.h"
#include "Context.h"
#include "AwesomiumHelper.h"
#include "GameContext.h"

HUD::HUD(GameContext* gamecontext, LevelManager* levelmanager)
{
	this->gamecontext = gamecontext;
	this->levelmanager = levelmanager;
	this->awesomium = new AwesomiumHelper{ gamecontext->context->web_core, "file:///Resources/html-game/HUD.html", 960, 640 };

	view.setSize(960, 640);
	view.setCenter(480, 320);
}

HUD::~HUD()
{
	delete awesomium;
}

bool HUD::Update()
{
	bool update = false;

	update = SetHealth( gamecontext->player->getHealth() ) ? true : update;
	update = SetLevel( levelmanager->getCurrentLevelIndex() ) ? true : update;

	return update;
}

bool HUD::SetHealth(int value)
{
	if(health != value)
	{
		health = value;
		awesomium->JavaScriptCall("UpdateHealth", health);
		return true;
	}
	return false;
}

bool HUD::SetLevel(int value)
{
	if (level != value)
	{
		level = value;
		awesomium->JavaScriptCall("UpdateLevel", levelmanager->getCurrentLevel());
		return true;
	}
	return false;
}