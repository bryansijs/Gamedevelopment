#include "stdafx.h"
#include "LevelManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "Dirent/dirent.h"
#include <iostream>


LevelManager::LevelManager()
{
	LoadAllLevels();
}


LevelManager::~LevelManager()
{
}

void LevelManager::LoadAllLevels()
{
	DIR *dir;
	struct dirent *ent;

	/* Open directory stream */
	dir = opendir("./Resources/levels/");
	if (dir != NULL) {

		/* Print all files and directories within the directory */
		int i = 0;
		while ((ent = readdir(dir)) != NULL) {
			switch (ent->d_type) {
			case DT_REG:
				allLevels[i] = std::string(ent->d_name);
				i++;
				break;
			default:
				break;
			}
		}
		closedir(dir);
	}
	else {
		/* Could not open directory */
		std::cerr << "Cannot open directory ./Resources/levels/";
		exit(EXIT_FAILURE);
	}
}

void LevelManager::swapSequence(int first, int second)
{
	std::string temp = allLevels[second];
	allLevels[second] = allLevels[first];
	allLevels[first] = temp;
}

std::vector<std::string> LevelManager::getAllLevels()
{
	std::vector<std::string> levels;
	for (int i = 0; i < allLevels.size(); i++)
	{
		levels.push_back(allLevels[i]);
	}
	return levels;
}

const char* LevelManager::getCurrentLevel()
{
	return allLevels[currentLevelNumber].c_str();
}

const char* LevelManager::getNextLevelName()
{
	if(!allLevels.empty())
	{
		currentLevelNumber += 1;
		return allLevels[currentLevelNumber].c_str();
	}
	return nullptr;
}
