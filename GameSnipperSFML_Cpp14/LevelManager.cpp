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
				std::cout << ent->d_name;
				char* newFile = new char (ent->d_name);
				allLevels.push_back(ent->d_name);
				break;
			default:
				break;
				//printf("%s*\n", ent->d_name);
			}
		}

		closedir(dir);

	}
	else {
		/* Could not open directory */
		printf("Cannot open directory ./Resources/levels/Level_1.json");
		exit(EXIT_FAILURE);
	}
}

