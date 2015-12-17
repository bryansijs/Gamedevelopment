#pragma once
#include "BaseState.h"
#include "LevelManager.h"
#include "PlayerActions.h"
#include "StorylineManager.h"

class StateManager;
class Context;
class GameContext;

class square;


class GameActions;
class AwesomiumHelper;


class GameState: public BaseState
{
public:
	GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager);
	~GameState();

	void Update() override;
	void Terminate() override;
	void StartNextLevel();
	bool showFPS = false;
	bool isPause = false;
private:
	StateManager* stateManager;

	LevelManager* levelManager;
	Context* maincontext;

	GameContext* gameContext;

	PlayerActions* playerActions;
	GameActions* gameActions;

	sf::View storyview;
	AwesomiumHelper* storyline;
	StorylineManager* storylineManager;

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
