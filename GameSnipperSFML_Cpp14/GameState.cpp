#include "stdafx.h"
#include "GameState.h"
#include  "gameloop.h"


void GameState::Run()
{
	GameLoop* gameLoop = new GameLoop(this->context);
	gameLoop->run();
}

void GameState::Terminate()
{
	delete this;
}

GameState::GameState(Context* c, StateManager* stateManager)
{
	this->context = c;
	this->stateManager = stateManager;
}

GameState::~GameState()
{
}