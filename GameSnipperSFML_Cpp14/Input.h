#pragma once
#include <string>
#include <SFML/Window/Keyboard.hpp>

using namespace std;

namespace sf {
	class Event;
}

class Input
{
	friend class Main;
public:
	Input();
	~Input();

	static std::string TranslateKey(sf::Keyboard::Key key);
	static bool GetKeyDown(string key);
	static bool GetKeyUp(string key);
	static void EventOccured(sf::Event occuredEvent);
};