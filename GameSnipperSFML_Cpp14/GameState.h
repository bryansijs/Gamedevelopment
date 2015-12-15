#pragma once
#include "BaseState.h"
#include "LevelManager.h"
#include "PlayerActions.h"

class StateManager;
class Context;
class GameContext;

class square;


class GameActions;


class GameState: public BaseState
{
public:
	GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager);
	~GameState();

	void Update() override;
	void Terminate() override;
	void StartNextLevel();

	bool isPause = false;
private:
	StateManager* stateManager;

	LevelManager* levelManager;
	Context* maincontext;

	GameContext* gameContext;
	void DrawFPS();

	PlayerActions* playerActions;
	GameActions* gameActions;

	void DestroyGameObjects();
	void DebugBodies();
	void MenuEnd(int option);

public:
	bool isPause = false;
	bool showFPS = false;
	void Update();
	void Terminate();
	void StartNextLevel();

	GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager);
	~GameState();
};
