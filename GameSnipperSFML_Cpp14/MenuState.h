#pragma once
class Context;
class MenuState
{
	Context* context;
public:
	void run();
	MenuState(Context* context);
	~MenuState();
};

