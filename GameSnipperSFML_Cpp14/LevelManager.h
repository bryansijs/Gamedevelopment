#pragma once
#include <vector>

class Level;
class LevelManager
{
	std::vector<char*> allLevels;

	void getAllLevels();

public:
	LevelManager();
	~LevelManager();
};

