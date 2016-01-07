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
	bool load = true;
	Context* context;
	WinContext* winContext;
	LevelManager* levelManager;
	sf::Image screenshot;
	ScoreManager* scoreManager;

	void SetHighscore();
	void addNameCharacter(const char* character);
	void setScore(int score);

public:
	WinState(Context* context, StateManager* stateManager, LevelManager* levelManager, sf::Image screenshot, ScoreManager* scoreManager);
	~WinState();

	void Update();
	void ToMenu();
};

