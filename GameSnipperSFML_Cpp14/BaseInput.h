#pragma once

#include <SFML/Graphics.hpp>

class BaseInput
{
public:
	BaseInput();
	void CatchInput();
	virtual ~BaseInput();
	void RemoveAllActiveKeys();
protected:
	std::vector<std::string> activeKeys;
	virtual void ProcessKeyActions() {};
	void AddActiveKey(std::string key);
	void RemoveActiveKey(std::string key);
};

