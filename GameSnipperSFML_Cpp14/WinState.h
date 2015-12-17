#pragma once
#include "BaseState.h"
#include <Awesomium/WebCore.h>
#include "LevelManager.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

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
public:
	WinState(Context* context, StateManager* stateManager, LevelManager* levelManager, sf::Image screenshot);
	~WinState();

	void Update();
	void ToMenu();
};

