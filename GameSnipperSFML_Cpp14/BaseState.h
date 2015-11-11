#pragma once
class BaseState
{
public:
	bool terminate = false;

	virtual void Update() {};
	virtual void Terminate() {};
};

