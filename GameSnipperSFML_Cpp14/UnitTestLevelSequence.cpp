#include "stdafx.h"
#include "UnitTestLevelSequence.h"
#include "MenuState.h"
#include "Context.h"
#include "StateManager.h"
#include "LevelManager.h"
#include "UnitTest.h"


UnitTestLevelSequence::UnitTestLevelSequence()
{
	LevelManager* levelManager = new LevelManager();

	std::vector<std::string> levels = levelManager->getAllLevels();
	bool nextLevelBool = levels.front() == levelManager->getNextLevelName();
	bool currentLevelBool = levels.front() == levelManager->getCurrentLevel();
	
	levelManager->getNextLevelName();
	levelManager->swapSequence(1, 2);

	bool swapLevelBool = levels.front() == levelManager->getCurrentLevel();

	levelManager->getAllLevels().front() == levelManager->getCurrentLevel();
	UnitTest::Compare("GetCurrentLevel",currentLevelBool , true);
	UnitTest::Compare("NextLevel",nextLevelBool, true);
	UnitTest::Compare("SwapLevel", swapLevelBool, true);
}


UnitTestLevelSequence::~UnitTestLevelSequence()
{
}
