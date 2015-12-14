#pragma once
#include "BaseState.h"
#include "LevelManager.h"


class StateManager;
class Context;
class GameContext;
class square;
class GameState: public BaseState
{
private:
	StateManager* stateManager;

	LevelManager* levelManager;
	Context* maincontext;

	GameContext* gameContext;

	void DestroyGameObjects();
	void DebugBodies();
	void MenuEnd(int option);

	void Loading();
	void DoneLoading();

	void ReloadUI(char const* path);
	void DrawUI();
	void CreateTexture();

	void GetAd();
public:
	bool isPause = false;
	void Update();
	void Terminate();
	void StartNextLevel();

	GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager);
	~GameState();
};
