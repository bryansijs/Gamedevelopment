#pragma once

#include <SFML/Graphics.hpp>

class BaseInput
{
public:
	BaseInput();
	virtual ~BaseInput();
	void CatchInput();
	void AddActiveKey(std::string key);
	void RemoveActiveKey(std::string key);
	std::vector<std::string>* GetActiveKeys() { return &activeKeys; };
protected:
	std::vector<std::string> activeKeys;
};

