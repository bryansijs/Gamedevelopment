#include "stdafx.h"
#include "MoveBehaviour.h"

void MoveBehaviour::Update(sf::Vector2f viewPortPosition) {}
bool MoveBehaviour::checkVisible(int screenX, int screenY) { 
	
	return (
		this->getGameObject()->getPosition().x > screenX -64 && 
		this->getGameObject()->getPosition().x < screenX  + 64 + 960 &&
		this->getGameObject()->getPosition().y > screenY - 64 &&
		this->getGameObject()->getPosition().y < screenY  + 64 + 640);
}


bool MoveBehaviour::Replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}