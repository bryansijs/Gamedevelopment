#pragma once
#include "BaseState.h"
#include "LevelManager.h"
#include "PlayerActions.h"
#include "StorylineManager.h"

class ScoreManager;
class StateManager;
class Context;
class GameContext;

class square;


class GameActions;
class AwesomiumHelper;


class GameState: public BaseState
{
public:
	GameState(Context* context, StateManager* stateManager, LevelManager* levelmanager, ScoreManager* scoreManager);
	~GameState();

	void Update() override;
	void Terminate() override;
	void StartNextLevel();
	void StartWinState();
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

	sf::View storyview;
	sf::View loadingView;
	AwesomiumHelper* storyline;
	AwesomiumHelper* loadingScreen;
	StorylineManager* storylineManager;

	void DestroyGameObjects();
	void DebugBodies();
	void MenuEnd(int option);

	void Loading();
	void DoneLoading();

	void DrawLoadingScreen();

	std::string GetAd();
	std::string GetTip();
	std::vector<std::string> GetFilesInDirectory(const char* directory);
};
