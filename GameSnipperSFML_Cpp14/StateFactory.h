#pragma once
#include <string>
#include <map>

class Context;
class BaseState;

class StateFactory
{
	std::map<std::string, BaseState> state_map;
public:
	void startNextState(std::string state_name, Context* c, BaseState* current);
	StateFactory();
	~StateFactory();
};

