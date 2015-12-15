#pragma once
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <map>

using namespace std;

namespace sf {
	class Event;
}

class Input
{
	friend class Main;
public:
	static string GetKey(sf::Keyboard::Key key);
	static sf::Keyboard::Key GetKey(const string & key);
	static bool GetKeyDown(string key);
	static bool GetKeyUp(string key);
	static void EventOccured(sf::Event occuredEvent);
	static string GetLastPressed();
	static void ClearLastPressed();
private:
	static map<string, sf::Keyboard::Key> keys;
	static string LastPressed;
};