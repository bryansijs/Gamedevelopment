#pragma once
#include "BaseState.h"
#include <Awesomium/WebCore.h>
#include "LevelManager.h"
#include "ScoreManager.h"

class StateManager;
class Context;
class WinContext;

class WinState : public BaseState
{
private:
	void ReloadPage();

	StateManager* stateManager;
	bool load = true;
	Context* context;
	WinContext* winContext;
	LevelManager* levelManager;
	ScoreManager* scoreManager;
	void SetHighscore();
	void addNameCharacter(const char* character);
	void setScore(int score);
	void addScore(std::string name, int score);

public:
	WinState(Context* context, StateManager* stateManager, LevelManager* levelManager, ScoreManager* scoreManager);
	~WinState();

	void Update();
	void ToMenu();
};

