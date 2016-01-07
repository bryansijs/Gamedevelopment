#pragma once
#include <map>
#include <vector>

class Level;
class LevelManager
{
	int currentLevelNumber = 0;
	std::map<int,std::string> allLevels;
	void LoadAllLevels();
public:
	void swapSequence(int first, int second);
	std::vector<std::string> getAllLevels();
	std::string getCurrentLevel();
	std::string getNextLevelName();
	LevelManager();
	~LevelManager();
};