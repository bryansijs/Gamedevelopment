#pragma once
class Context;
class GameLoop
{
public:
	GameLoop(Context* context);
	~GameLoop();

	void run();

private:
	Context* context;
};

