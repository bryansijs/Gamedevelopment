#include "stdafx.h"
#include "PlayerMovement.h"
#include "Input.h"
#include <iostream>
#include <map>
#include <functional>

using namespace std;

PlayerMovement::PlayerMovement()
{
}

PlayerMovement::~PlayerMovement()
{
}

typedef void(*ScriptFunction)(void);

map<Key, ScriptFunction> keys = {
	{ Key::W, Keyboard::W },
	{ Key::A, Keyboard::A },
	{ Key::S, Keyboard::S },
	{ Key::D, Keyboard::D },
	{ Key::Left, Keyboard::Left },
	{ Key::Right, Keyboard::Right },
	{ Key::Up, Keyboard::Up },
	{ Key::Down, Keyboard::Down },
	{ Key::Space, Keyboard::Space },
	{ Key::E, Keyboard::E },
	{ Key::Num1, Keyboard::Num1 },
	{ Key::Num2, Keyboard::Num2 },
	{ Key::Num3, Keyboard::Num3 },
	{ Key::Num4, Keyboard::Num4 },
	{ Key::Num5, Keyboard::Num5 },
};

void PlayerMovement::MoveEvent()
{

}

