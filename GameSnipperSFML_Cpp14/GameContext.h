#pragma once

class Context;

class GameContext
{
public:
	GameContext(Context* context);
	~GameContext();

	Context* context;
};

