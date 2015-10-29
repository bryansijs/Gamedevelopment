#pragma once
class BaseState
{
	
public:
	bool running = false;
	void SetRunning(bool boolean) { running = boolean;};
	virtual void Run() {};
	virtual void Terminate() {};
};

