#pragma once

#include <SFML/Graphics.hpp>

class BaseInput
{
public:
	BaseInput();
	virtual ~BaseInput();

	void CatchSingleInput();
	void CatchInput();
protected:
	std::vector<std::string> activeKeys;
	void AddActiveKey(std::string key);
	void RemoveActiveKey(std::string key);
};

