#include "stdafx.h"
#include "StorylineManager.h"
#include <SFML/Audio/Sound.hpp>
#include "Time.h"

std::string StorylineManager::current;
std::queue<std::string> StorylineManager::messages;
float StorylineManager::timer = 2;
sf::Sound* StorylineManager::music;
sf::SoundBuffer StorylineManager::sfx;

void StorylineManager::Add(std::string message)
{
	messages.push(message);
}

bool StorylineManager::Updated()
{
	if (timer > 0)
	{
		timer -= Time::deltaTime;
		return false;
	}

	if (messages.size() == 0 && current == "")
		return false;

	if (messages.size() > 0)
	{
		current = messages.front();
		messages.pop();
		TimerReset();
		PlaySound();
		return true;
	}

	current = "";
	return true;
}

std::string StorylineManager::GetText()
{
	return current;
}

void StorylineManager::PlaySound()
{
	sfx.loadFromFile("./Resources/music/notification.ogg");
	music = new sf::Sound(sfx);
	music->setVolume(100.0f);
	music->setLoop(false);
	music->play();
}