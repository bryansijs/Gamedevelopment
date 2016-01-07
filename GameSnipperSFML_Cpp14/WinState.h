#pragma once
#include "BaseState.h"
#include <Awesomium/WebCore.h>
#include "LevelManager.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "ScoreManager.h"

class StateManager;
class Context;
class WinContext;

class WinState : public BaseState
{
private:
	void ReloadPage();

	StateManager* stateManager;

	Context* context;
	WinContext* winContext;
	LevelManager* levelManager;
	sf::Image screenshot;
	ScoreManager* scoreManager;
	bool load = true;
public:
	WinState(Context* context, StateManager* stateManager, LevelManager* levelManager, sf::Image screenshot, ScoreManager* scoreManager);
	~WinState();

	void Update();
	void ToMenu();
};

