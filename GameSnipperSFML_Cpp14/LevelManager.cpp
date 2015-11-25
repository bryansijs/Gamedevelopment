#include "stdafx.h"
#include "LevelManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "Dirent/dirent.h"
#include <iostream>


LevelManager::LevelManager()
{
	getAllLevels();
}


LevelManager::~LevelManager()
{
}

void LevelManager::getAllLevels()
{
	DIR *dir;
	struct dirent *ent;

	/* Open directory stream */
	dir = opendir("./Resources/levels/");
	if (dir != NULL) {

		/* Print all files and directories within the directory */
		while ((ent = readdir(dir)) != NULL) {
			switch (ent->d_type) {
			case DT_REG:
				allLevels.push_back(std::string(ent->d_name));
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

