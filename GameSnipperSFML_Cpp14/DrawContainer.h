#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

class DrawBehaviour;

class DrawContainer
{
public:
	DrawContainer();
	~DrawContainer();

	void Draw(sf::RenderWindow* window, sf::Vector2f viewPortPosition);
	void AddBehaviour(DrawBehaviour* behaviour);
	void RemoveBehaviour(DrawBehaviour* behaviour);

	void addDiscoveryId(int id) { Discoverdids.push_back(id); };
	std::vector<int> getDiscoveredids() { return Discoverdids; };

	bool checkIfidIsDiscoverd(int id);
	
private:
	std::vector<DrawBehaviour*> behaviours;
	std::vector<int> Discoverdids;
};

