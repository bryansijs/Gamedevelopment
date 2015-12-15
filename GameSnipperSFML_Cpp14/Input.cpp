#include "stdafx.h"
#include "Input.h"
#include <SFML/Graphics.hpp>

sf::Event event;
string Input::LastPressed;

map<string, sf::Keyboard::Key> Input::keys = {
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
	{ "Return", sf::Keyboard::Return },
	{ "Y", sf::Keyboard::Y },
	{ "U", sf::Keyboard::U },
	{ "/", sf::Keyboard::Slash }
};

string Input::GetKey(sf::Keyboard::Key key)
{
	for (auto iterator = keys.begin(); iterator != keys.end(); ++iterator)
	{
		if(iterator->second == key)
		{
			return iterator->first.c_str();
		}
	}
	return "";
}

sf::Keyboard::Key Input::GetKey(const string & key)
{
	auto it = keys.find(key);
	if (it != keys.end())
	{
		return keys.at(key);
	}
}

bool Input::GetKeyDown(string key)
{
	return event.type == sf::Event::KeyPressed && event.key.code == GetKey(key);
}

bool Input::GetKeyUp(string key)
{
	return event.type == sf::Event::KeyReleased && event.key.code == GetKey(key);
}

void Input::EventOccured(sf::Event occuredEvent)
{
	event = occuredEvent;
	if(event.type == sf::Event::KeyPressed)
		LastPressed = GetKey(event.key.code);
}

string Input::GetLastPressed()
{
	return LastPressed;
}


void Input::ClearLastPressed()
{
	LastPressed = "";
}