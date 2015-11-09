#include "stdafx.h"
#include "Context.h"
#include <iostream>
#include "UnitTestMain.h"

#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2d/Box2D.h>

#include "LevelImporter.h"
#include "MenuState.h"
#include "StateManager.h"
#include "GameState.h"

bool quitGame = false;

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		StateManager* stateManager = new StateManager();

		UnitTestMain utm;
		Context* context{ new Context(960,640) };
		context->window.setMouseCursorVisible(false);

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

