#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#define MAX_NUMBER_OF_ITEMS 3

class PauseMenu
{
public:
	PauseMenu(float width, float height);
	~PauseMenu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }
	int KeyHandler();
	void setPositions(float levelx, float  levely, float  width, float  height);
private:
	int selectedItemIndex;
	int KeyValue();

	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];


	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Texture pointerTexture;
	sf::Sprite pointerSprite;

	sf::Text title;

	sf::RectangleShape rect;

	sf::SoundBuffer sfxSound;
	sf::Sound sfx;
};

