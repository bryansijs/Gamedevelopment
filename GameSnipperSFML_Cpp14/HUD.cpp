#include "stdafx.h"
#include "HUD.h"
#include "Context.h"
#include "AwesomiumHelper.h"
#include "GameContext.h"
#include "BaseItem.h"
#include "Gun.h"

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

bool HUD::SetItems(int keyAmount,int  potions)
{
	// build item list
	// key=0, potions red=potions1, potions blue=potions2
	std::string temp = "";
	for (int i = 0; i < keyAmount; i++)
	{
		temp = temp + ",0";
	}


	for (int i = 0; i < potions; i++)
	{
		temp = temp + ",1";
	}
	/*for (auto &potion : potions)
	{


		std::string test = potion.first->getItemType();
		for (int i = 0; i < potion.second; i++)
		{
		
		}
	}*/
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
	Gun* current = static_cast<Gun*>(gamecontext->player->GetEquipedGun());
	if (gun != current->GetName())
	{
		gun = current->GetName();

		if(gun == "pistol")
			awesomium->JavaScriptCall("setWeapon", 0, false);
		if (gun == "rifle")
			awesomium->JavaScriptCall("setWeapon", 1, false);

		return true;
	}
	return false;
}