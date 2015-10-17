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

void PlayerMovement::Move(float deltaTime)
{
	if (Input::GetKeyDown(KeyMapping::GetKey("move-up")))
	{
		x += 1.0f;
	}
	if (Input::GetKeyDown(KeyMapping::GetKey("move-down")))
	{
		x += -1.0f;
	}
	if (Input::GetKeyDown(KeyMapping::GetKey("move-left")))
	{
		y += -1.0f;
	}
	if (Input::GetKeyDown(KeyMapping::GetKey("move-right")))
	{
		y += 1.0f;
	}


}

void PlayerMovement::SetX(float x)
{

}

void PlayerMovement::SetY(float y)
{

}