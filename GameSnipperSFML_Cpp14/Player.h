#pragma once
#include <map>
#include "Unit.h"
#include "BaseItem.h"

class MoveContainer;
class DrawContainer;
class BaseItem;
class Player : public Unit
{
private:
	int keyAmount = 0;
	
	int potions = 0;
//	std::map<BaseItem*, int> potions;
	std::vector<BaseItem*> ammo;
	std::vector<BaseItem*> guns;

	void AddKey(BaseItem* item) { keyAmount++; }
	void AddAmmo(BaseItem* item);
	void AddGun(BaseItem* item);
	void AddPotion(BaseItem* item);

	std::map<std::string, void(Player::*)(BaseItem* item)> itemFunctions = {
		{ "Potion", &Player::AddPotion },
		{ "Ammo", &Player::AddAmmo },
		{ "Gun", &Player::AddGun },
		{ "Key", &Player::AddKey },
	};

	BaseItem* equipedGun;
	bool godMode = false;
public:
	Player(MoveContainer* moveContainer, DrawContainer* drawContainer, GameObjectContainer *useContainer, b2World* world);
	Player();
	~Player();

	void removeKey(){keyAmount--;}
	int getKey() { return keyAmount; }

	int getPotions()
	{
		return this->potions;
	}

	void AddItem(BaseItem* item);

	void EnableGodMode();
	void DisableGodMode();
	bool GetGodMode();
	void usePotion();
	void EquipGun(int slot);
	BaseItem* GetEquipedGun();

	virtual void startContact(b2Fixture* fixture);
	virtual void endContact(b2Fixture* fixture);
};

