#pragma once

#include "GameObject.h"

class MoveBehaviour
{
private:

	std::vector<std::string> direction;
	std::vector<std::string> directions;
	std::string shotDirection;

public:
	virtual void Update(sf::Vector2f viewPortPosition);
	virtual bool checkVisible(int screenX, int screenY);

	GameObject* getGameObject() { return gameObject; };

	void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }

	void ClearObject() { this->gameObject = nullptr; }

	std::vector<std::string> getDirection() {
		return direction;
	}

	std::string getDirection(int dir) {
		return directions[dir];
	}

	void addDirection(std::string  direction) {
		this->direction.push_back(direction);
	}

	void swapDirections(std::vector<std::string> directions) {
		this->directions.swap(directions);
	}

	void clearDirection()
	{
		this->direction.clear();
	}

	int getDirectionSize()
	{
		return directions.size();
	}

	std::string getShotDirection() { return shotDirection; }
	void setShotDirection(std::string dir) { this->shotDirection = dir; }



protected:
	GameObject* gameObject;
	bool Replace(std::string& str, const std::string& from, const std::string& to);


};

