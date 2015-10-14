#include "stdafx.h"
#include "Input.h"

#include <SFML/Graphics.hpp>

using namespace sf;

Input::Input()
{
}

Input::~Input()
{
}

Event event;

Keyboard::Key GetKey(const Key & key)
{
	map<Key, Keyboard::Key> keys = {
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

	return keys.at(key);
}

bool Input::GetKeyDown(Key key)
{
	return event.type == Event::KeyPressed && event.key.code == GetKey(key);
}

bool Input::GetKeyUp(Key key)
{
	return event.type == Event::KeyReleased && event.key.code == GetKey(key);
}

void Input::EventOccured(sf::Event occuredEvent)
{
	event = occuredEvent;
}