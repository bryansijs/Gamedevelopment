#pragma once

#include <iostream>
#include <map>

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
	// TODO: Move to friend class
	static void EventOccured(sf::Event occuredEvent);
private:

};