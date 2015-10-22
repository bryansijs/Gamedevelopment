#include <iostream>
#include "stdafx.h"
#include "game_state.h"
#include "GameLoop.h"
#include "Context.h"



game_state coreState;
bool quitGame = false;
//using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	Context* context{ new Context(960,640) };
	GameLoop* loop{ new GameLoop(context) };
	loop->run();
	
}

