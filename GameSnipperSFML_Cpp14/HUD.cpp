#include "stdafx.h"
#include "HUD.h"
#include "Context.h"
#include "AwesomiumHelper.h"
#include "GameContext.h"
#include "BaseItem.h"

HUD::HUD(GameContext* gamecontext)
{
	this->gamecontext = gamecontext;
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
	update = SetItems(gamecontext->player->getKey(), gamecontext->player->getPotions()) ? true : update;
	update = SetWeapons() ? true : update;

	if (update)
		awesomium->UpdateWebcore();

	return update;
}

bool HUD::SetHealth(int value)
{
	if(health != value)
	{
		health = value;
		awesomium->JavaScriptCall("setHealth", health, false);
		return true;
	}
	return false;
}

bool HUD::SetItems(int keyAmount, std::map<BaseItem*, int> potions)
{
	// build item list
	// key=0, potions1=potions1, potions2=potions2
	std::string temp = "";
	for (int i = 0; i < keyAmount; i++)
	{
		temp = temp + ",0";
	}

	for (auto &potion : potions)
	{
		std::string test = potion.first->getItemType();
		// todo: switch potion types
		temp = temp + ",1";
	}
	temp.erase(0,1);

	if (temp != items)
	{
		items = temp;
		awesomium->JavaScriptCall("setItems", items, false);
		return true;
	}
	return false;
}

bool HUD::SetWeapons()
{
	if (false)
	{
		awesomium->JavaScriptCall("setHealth", health, false);
		return true;
	}
	return false;
}