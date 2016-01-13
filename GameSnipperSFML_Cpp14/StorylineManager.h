#pragma once
#include <queue>
#include <SFML/Audio/SoundBuffer.hpp>

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
	static void TimerReset() { timer = 3; };

	static sf::Sound* music;
	static sf::SoundBuffer sfx;
	static void PlaySound();

};