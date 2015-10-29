#include "stdafx.h"
#include "game_state.h"
#include "GameLoop.h"
#include "Context.h"

#include <iostream>

game_state coreState;
bool quitGame = false;

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		Context* context{ new Context(960,640) };
		GameLoop* loop{ new GameLoop(context) };
		loop->run();
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

