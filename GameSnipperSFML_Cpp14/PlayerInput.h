#pragma once

#include <SFML/Graphics.hpp>

class PlayerInput
{
public:
	PlayerInput();
	~PlayerInput();

	void CatchInput();
	void AddActiveKey(std::string key);
	void RemoveActiveKey(std::string key);
	std::vector<std::string> GetActiveKeys();
private:
	std::vector<std::string> activeKeys;
};

