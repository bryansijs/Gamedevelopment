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

bool quitGame = false;

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//testing::InitGoogleTest(&argc, argv);
	
	//RUN_ALL_TESTS();

	try
	{
		Context* context{ new Context(960,640) };
		//TODO: State manager
		//TODO: Only if game start with state
		
		//GameLoop* loop{ new GameLoop(context) };
		//loop->run();
		
		MenuState* menu{ new MenuState(context) };
		menu->run();
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

