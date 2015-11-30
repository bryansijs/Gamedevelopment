#pragma once

#include <SFML/Graphics.hpp>

class BaseInput
{
public:
	BaseInput();
	virtual ~BaseInput();

	void CatchInput();
	virtual void ProcessActions() {};
protected:
	virtual void ExecuteActions() {};

	std::vector<std::string> activeKeys;
	void AddActiveKey(std::string key);
	void RemoveActiveKey(std::string key);
};

