#pragma once
#include <vector>

class Level;
class LevelManager
{
	std::vector<std::string> allLevels;

	void getAllLevels();

public:
	LevelManager();
	~LevelManager();
};

