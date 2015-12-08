#pragma once
#include <queue>

class StorylineManager
{
public:
	static void Add(std::string message);
	static bool Updated();
	static std::string GetText();
private:
	static std::string current;
	static std::queue<std::string> messages;
	static float timer;
	static void TimerReset() { timer = 500; };
};