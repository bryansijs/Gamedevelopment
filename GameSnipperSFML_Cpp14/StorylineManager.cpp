#include "stdafx.h"
#include "StorylineManager.h"

std::string StorylineManager::current;
std::queue<std::string> StorylineManager::messages;
float StorylineManager::timer = 0;

void StorylineManager::Add(std::string message)
{
	messages.push(message);
}

bool StorylineManager::Updated()
{
	if (timer > 0)
	{
		timer--;
		return false;
	}

	if (messages.size() == 0 && current == "")
		return false;

	if (messages.size() > 0)
	{
		current = messages.front();
		messages.pop();
		TimerReset();
		return true;
	}

	current = "";
	return true;
}

std::string StorylineManager::GetText()
{
	return current;
}