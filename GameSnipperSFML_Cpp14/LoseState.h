#pragma once
#include "BaseState.h"
#include <Awesomium/WebCore.h>
#include "LevelManager.h"

class StateManager;
class Context;
class LoseContext;

class LoseState : public BaseState
{
private:
	void ReloadPage();

	StateManager* stateManager;

	Context* context;
	LoseContext* loseContext;
	LevelManager* levelManager;
	sf::Image screenshot;
public:
	LoseState(Context* context, StateManager* stateManager, LevelManager* levelManager, sf::Image screenshot);
	~LoseState();

	void Update();
	void ToMenu();
};

