#pragma once
#include <string>

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

	static bool GetKeyDown(string key);
	static bool GetKeyUp(string key);
	static void EventOccured(sf::Event occuredEvent);
};