#pragma once
#include "BaseState.h"
#include "LevelManager.h"
#include "PlayerActions.h"

class ScoreManager;
class StateManager;
class Context;
class GameContext;

class square;


class GameActions;


class GameState: public BaseState
{
public:
	GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager, ScoreManager* scoreManager);
	~GameState();

	void Update() override;
	void Terminate() override;
	void StartNextLevel();
	bool showFPS = false;
	bool isPause = false;
private:
	StateManager* stateManager;
	ScoreManager* scoreManager;
	LevelManager* levelManager;
	Context* maincontext;

	GameContext* gameContext;

	PlayerActions* playerActions;
	GameActions* gameActions;

	void DestroyGameObjects();
	void DebugBodies();
	void MenuEnd(int option);

	void Loading();
	void DoneLoading();

	void ReloadUI(char const* path);
	void DrawUI();
	void CreateTexture();

	void GetAd();
};
