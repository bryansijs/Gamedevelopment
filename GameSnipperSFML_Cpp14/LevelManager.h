#pragma once
#include <map>

class Level;
class LevelManager
{
	int currentLevelNumber = -1;

	std::map<int,std::string> allLevels;

	void getAllLevels();

public:
	void swapSequence(int first, int second);
	const char* getCurrentLevel();
	const char* getNextLevelName();
	LevelManager();
	~LevelManager();
};