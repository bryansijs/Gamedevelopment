#include "stdafx.h"
#include "StateFactory.h"
#include "MenuState.h"
#include "GameLoop.h"


void StateFactory::startNextState(std::string state_name, Context* c,BaseState* current)
{

	if(state_name == "newGame")
	{
		delete current;
		GameLoop* unit =  new GameLoop(c);
		unit->run();
	}
}

StateFactory::StateFactory()
{
	//state_map["newGame"] = new BaseState();

}


StateFactory::~StateFactory()
{
}
