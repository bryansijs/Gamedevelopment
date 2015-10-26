#include "stdafx.h"
#include "Context.h"
#include <iostream>

#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2d/Box2D.h>
#include <gtest/gtest.h>

#include "LevelImporter.h"
#include "MenuState.h"
#include "StateManager.h"
#include "GameState.h"

bool quitGame = false;

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//testing::InitGoogleTest(&argc, argv);
	
	//RUN_ALL_TESTS();

	try
	{
		StateManager* stateManager = new StateManager();
		Context* context{ new Context(960,640) };

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

