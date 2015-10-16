#pragma once

#include <iostream>
#include <map>
#include <functional>

using namespace std;

namespace sf {
	class Event;
}

enum class Key : unsigned int {
	W,
	A,
	S,
	D,
	Left,
	Right,
	Up,
	Down,
	Lmouse,
	Space,
	E,
	Num1,
	Num2,
	Num3,
	Num4,
	Num5
};

class Input
{
	friend class Main;
public:
	Input();
	~Input();

	static bool GetKeyDown(Key key);
	static bool GetKeyUp(Key key);
	// TODO: Move to friend class
	static void EventOccured(sf::Event occuredEvent);
private:

};