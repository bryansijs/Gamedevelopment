#pragma once
class BaseState
{
	
public:
	bool running = false;
	virtual void Run() {};
	virtual void Terminate() {};
};

