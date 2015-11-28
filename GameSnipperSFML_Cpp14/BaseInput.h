#pragma once

#include <SFML/Graphics.hpp>

class BaseInput
{
public:
	BaseInput();
	void CatchInput();
	virtual ~BaseInput();
protected:
	std::vector<std::string> activeKeys;
	virtual void ProcessKeyActions() {};
private:
	void AddActiveKey(std::string key);
	void RemoveActiveKey(std::string key);
};

