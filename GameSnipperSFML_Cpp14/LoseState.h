#pragma once
#include "BaseState.h"
#include <Awesomium/WebCore.h>
#include "LevelManager.h"

class ScoreManager;
class StateManager;
class Context;
class LoseContext;

class LoseState : public BaseState
{
private:
	void ReloadPage();

	StateManager* stateManager;
	ScoreManager* scoreManager;

	Context* context;
	LoseContext* loseContext;
	LevelManager* levelManager;
public:
	LoseState(Context* context, StateManager* stateManager, LevelManager* levelManager, ScoreManager* scoreManager);
	~LoseState();

	void Update();
	void ToMenu();
};

