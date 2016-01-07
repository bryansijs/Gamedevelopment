#include "stdafx.h"
#include "Player.h"
#include "MoveContainer.h"
#include "DrawContainer.h"
#include <Box2D/Box2D.h>
#include "NormalMoveBehaviour.h"
#include "PlayerDrawBehaviour.h"
#include "EndTile.h"
#include "GameObjectFactory.h"

Player::Player(MoveContainer* moveContainer, DrawContainer* drawContainer, GameObjectContainer* useContainer, b2World* world)
{
	this->setSpeed(250.0f);
	this->setMoveContainer(moveContainer);
	this->setDrawContainer(drawContainer);

	this->SetMoveBehaviour(new NormalMoveBehaviour(this));
	this->setDrawBehaviour(new PlayerDrawBehaviour(this, 10, "Player.png"));

	this->setSize(32, 32);

	//this->createBoxDynamic(*world);
	this->getDrawContainer()->AddBehaviour(getDrawBehaviour());
	this->setUseContainer(useContainer);

	this->SetAnimationStates(3);
	this->setHealth(100);

	WeaponFactory weaponFactory;
	std::map<std::string, std::string> properties = {
		{ "wType", "Pistol" },
		{ "pType", "Bullet" }
	};

	this->AddGun((BaseItem*)weaponFactory.Create(properties, useContainer));

	// Equip a second gun
	std::map<std::string, std::string> rifleProperties = {
		{ "wType", "Rifle" },
		{ "pType", "Bullet" }
	};

	this->AddGun((BaseItem*)weaponFactory.Create(rifleProperties, useContainer));
	this->EquipGun(1);
}

Player::Player()
{
	this->SetMoveBehaviour ( new NormalMoveBehaviour(this) );
	this->setDrawBehaviour(new PlayerDrawBehaviour(this, 10, "Player.png"));
	this->setHealth(100);

	
}

Player::~Player()
{
	
}

void Player::AddItem(BaseItem* item) {
	std::map<std::string, void(Player::*)(BaseItem* item)>::iterator  it;
	for (it = itemFunctions.begin(); it != itemFunctions.end(); it++) {
		if (it->first == item->getItemType()) {
			auto function = it->second;
			return (this->*function)(item);
		}
	}
}

void Player::EnableGodMode()
{
	this->godMode = true;
}

void Player::DisableGodMode()
{
	this->godMode = false;
}

bool Player::GetGodMode()
{
	return this->godMode;
}

void Player::EquipGun(int slot)
{
	if (guns.size() >= slot)
	{
		equipedGun = guns[slot - 1];
	}
}

BaseItem * Player::GetEquipedGun()
{
	return this->equipedGun;
}

void Player::startContact(b2Fixture* fixture)
{

}

void Player::endContact(b2Fixture * fixture)
{
}

void Player::AddAmmo(BaseItem* item) {

}

void Player::AddGun(BaseItem* item) {
	this->guns.push_back(item);
}

void Player::AddPotion(BaseItem* item) {

	std::map<BaseItem*, int>::iterator it;
	for (it = potions.begin(); it != potions.end(); it++) {
		if (it->first->getItemId() == item->getItemId())
		{
			it->second += 1;
			return;
		}
	}

	potions.insert(std::pair<BaseItem*, int>(item, 1));
}
