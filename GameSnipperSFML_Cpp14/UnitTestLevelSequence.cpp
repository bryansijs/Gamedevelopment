#include "stdafx.h"
#include "UnitTestLevelSequence.h"
#include "MenuState.h"
#include "Context.h"
#include "StateManager.h"
#include "LevelManager.h"


UnitTestLevelSequence::UnitTestLevelSequence()
{
	Context* maincontext = new Context(500,500);
	StateManager* stateManager = new StateManager();
	LevelManager* levelManager = new LevelManager();

	MenuState* menuState = new MenuState(maincontext, stateManager, levelManager);
}


UnitTestLevelSequence::~UnitTestLevelSequence()
{
}
