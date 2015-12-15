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
		std::string name = std::string("");
		/* Print all files and directories within the directory */
		int i = 0;
		while ((ent = readdir(dir)) != NULL) {
			switch (ent->d_type) {
			case DT_REG:
				name = std::string(ent->d_name);
				allLevels[i] = name.substr(0,std::string(ent->d_name).size()-5);
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
	first--;
	second--;
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

std::string LevelManager::getCurrentLevel()
{
	std::string result;
	result.append(allLevels[currentLevelNumber]);
	result.append(".json");
	return result;
}

std::string LevelManager::getNextLevelName()
{
	if(!allLevels.empty())
	{
		currentLevelNumber += 1;
		return getCurrentLevel();
	}
	return nullptr;
}
