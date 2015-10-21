#include "stdafx.h"
#include "game_state.h"
#include "GameLoop.h"
#include "Context.h"

#include <iostream>

#include <conio.h>
#include <thread>
#include <chrono> 
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2d/Box2D.h>

#include "application.h"
#include "method_dispatcher.h"
#include "js_delegate.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/BitmapSurface.h>
#include "LevelImporter.h"
#include <string>
#include "MenuState.h"

game_state coreState;
bool quitGame = false;

using namespace std;

using namespace Awesomium;	

int _tmain(int argc, _TCHAR* argv[])
{
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

