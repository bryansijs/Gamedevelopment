#pragma once
#include <map>
#include <string>
#include  <memory>
#include "Unit.h"
#include "BaseItem.h"


class MoveContainer;
class DrawContainer;
class BaseItem;
class Player : public Unit
{
private:
	int keyAmount = 0;
	
	std::map<BaseItem*, int> potions;
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



public:
	Player(MoveContainer* moveContainer, DrawContainer* drawContainer, b2World* world);
	Player(MoveContainer* moveContainer, DrawContainer* drawContainer, GameObjectContainer *useContainer, b2World* world);
	Player();
	~Player();

	void removeKey(){keyAmount--;}

	int getKey() { return keyAmount; }

	std::map<BaseItem*, int> getPotions()
	{
		return this->potions;
	}

	void AddItem(BaseItem* item);


};

