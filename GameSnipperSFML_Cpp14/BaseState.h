#pragma once
class BaseState
{
public:
	virtual ~BaseState() {};

	bool terminate = false;

	virtual void Update() {};
	virtual void Terminate() {};
};

