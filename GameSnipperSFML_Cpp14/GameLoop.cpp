#include <SFML\Graphics.hpp>
#include "stdafx.h"
#include "GameLoop.h"
#include "Context.h"
#include "Unit.h"
#include "DrawBehaviour.h"
#include "NormalDrawBehaviour.h"
#include "MoveBehaviour.h"
#include "LevelImporter.h"
#include "PlayerActions.h"
#include "Time.h"

LevelImporter* l;
Level* lev;
GameLoop::GameLoop(Context* c)
{
	this->context = c;
	//l = new LevelImporter(context->drawContainer);

	l->Import("./Resources/levels/Level_New.json");
	l->Prepare();
}

GameLoop::~GameLoop()
{

}

void GameLoop::run()
{
	
}