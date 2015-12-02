#include "stdafx.h"
#include "Input.h"

#include <SFML/Graphics.hpp>

Input::Input()
{
}

Input::~Input()
{
}

sf::Event event;

std::string Input::TranslateKey(sf::Keyboard::Key key)
{
	sf::Keyboard::Key incomingKey = key;

	map<sf::Keyboard::Key, string> keys = {
		{ sf::Keyboard::W, "W" },
		{ sf::Keyboard::A,"A" },
		{ sf::Keyboard::S, "S" },
		{ sf::Keyboard::D, "D" },
		{ sf::Keyboard::Left, "Left" },
		{ sf::Keyboard::Right, "Right" },
		{ sf::Keyboard::Up, "Up" },
		{ sf::Keyboard::Down, "Down" },
		{ sf::Keyboard::Space, "Space" },
		{ sf::Keyboard::E, "E" },
		{ sf::Keyboard::K, "K" },
		{ sf::Keyboard::L, "L" },
		{ sf::Keyboard::Num1, "Num1" },
		{ sf::Keyboard::Num2, "Num2" },
		{ sf::Keyboard::Num3, "Num3" },
		{ sf::Keyboard::Num4, "Num4" },
		{ sf::Keyboard::Num5, "Num5" },
		{ sf::Keyboard::Escape, "Esc" },
		{ sf::Keyboard::Return, "Return" }
	};

	auto it = keys.find(key);

	if (it != keys.end())
	{
		return keys.at(key);
	}
	return"";
}

sf::Keyboard::Key GetKey(const string & key)
{
	string incomingKey = key;

	map<string, sf::Keyboard::Key> keys = {
		{ "W", sf::Keyboard::W },
		{ "A", sf::Keyboard::A },
		{ "S", sf::Keyboard::S },
		{ "D", sf::Keyboard::D },
		{ "Left", sf::Keyboard::Left },
		{ "Right", sf::Keyboard::Right },
		{ "Up", sf::Keyboard::Up },
		{ "Down", sf::Keyboard::Down },
		{ "Space", sf::Keyboard::Space },
		{ "E", sf::Keyboard::E },
		{ "K", sf::Keyboard::K },
		{ "L", sf::Keyboard::L },
		{ "Num1", sf::Keyboard::Num1 },
		{ "Num2", sf::Keyboard::Num2 },
		{ "Num3", sf::Keyboard::Num3 },
		{ "Num4", sf::Keyboard::Num4 },
		{ "Num5", sf::Keyboard::Num5 },
		{ "Esc", sf::Keyboard::Escape },
		{ "Return", sf::Keyboard::Return }
	};

	auto it = keys.find(key);

	if (it != keys.end())
	{
		return keys.at(key);
	}
}

bool Input::GetKeyDown(string key)
{
	sf::Keyboard::Key pressedKey = GetKey(key);
	return event.type == sf::Event::KeyPressed && event.key.code == GetKey(key);
}

bool Input::GetKeyUp(string key)
{
	return event.type == sf::Event::KeyReleased && event.key.code == GetKey(key);
}

void Input::EventOccured(sf::Event occuredEvent)
{
	event = occuredEvent;
}