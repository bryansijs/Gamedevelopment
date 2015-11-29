#pragma once
#include <map>
#include <vector>

class Level;
class LevelManager
{
	int currentLevelNumber = -1;
	std::map<int,std::string> allLevels;
	void LoadAllLevels();
public:
	void swapSequence(int first, int second);
	std::vector<std::string> getAllLevels();
	const char* getCurrentLevel();
	const char* getNextLevelName();
	LevelManager();
	~LevelManager();
};