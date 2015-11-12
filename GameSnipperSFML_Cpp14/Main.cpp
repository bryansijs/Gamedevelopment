#include "stdafx.h"
#include "UnitTestMain.h"
#include <iostream>
#include "Context.h"
#include "MenuState.h"
#include "StateManager.h"

bool quitGame = false;

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		StateManager* stateManager = new StateManager();

		new UnitTestMain;

		Context* context = new Context(960, 640);
		MenuState* state = new MenuState(context, stateManager);

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

