#include "stdafx.h"
#include "UnitTestMain.h"
#include <iostream>
#include "Context.h"
#include "MenuContext.h"
#include "LevelImporter.h"
#include "MenuState.h"
#include "StateManager.h"
#include "ScoreManager.h"
#include "vld.h"

bool quitGame = false;

using namespace std;

//int _tmain(int artgc, _TCHAR* argv[])
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)  // GameSnipperSFML properties/linker/system/subsystem op WINDOWS zetten dan word de console gehide
{
	try
	{
		ScoreManager* scoreManager = new ScoreManager();
		StateManager* stateManager = new StateManager();
		LevelManager* levelManager = new LevelManager();

		//UnitTestMain utm;

		Context* context = new Context(960, 640);
		MenuState* state = new MenuState(context, stateManager,levelManager,scoreManager);

		stateManager->AddState(state);
		stateManager->RunState();
	}
	catch (std::exception e)
	{
		std::cerr << e.what();
	}
	catch (...)
	{
		std::cerr << "Default exception";
	}

	return 0;
}

