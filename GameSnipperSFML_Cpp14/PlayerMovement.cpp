#include "stdafx.h"
#include "PlayerMovement.h"
#include "KeyMapping.h"
#include "Input.h"

PlayerMovement::PlayerMovement()
{
}

PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::Move(float deltaTime, Player* player)
{
	if (Input::GetKeyDown(KeyMapping::GetKey("move-up")))
	{
		cout << "Move up\n";
		player->positions.y += -1.0f * (deltaTime / 10000);
	}
	if (Input::GetKeyDown(KeyMapping::GetKey("move-down")))
	{
		cout << "Move down\n";
		player->positions.y += 1.0f * (deltaTime / 10000);
	}
	if (Input::GetKeyDown(KeyMapping::GetKey("move-left")))
	{
		cout << "Move left\n";
		player->positions.x += -1.0f * (deltaTime / 10000);
	}
	if (Input::GetKeyDown(KeyMapping::GetKey("move-right")))
	{
		cout << "Move right\n";
		player->positions.x += 1.0f * (deltaTime / 10000);
	}
}

void PlayerMovement::SetX(float x)
{

}

void PlayerMovement::SetY(float y)
{

}