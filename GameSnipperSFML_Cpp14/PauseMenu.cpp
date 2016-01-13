#include "stdafx.h"
#include "PauseMenu.h"
#include "Input.h"

PauseMenu::PauseMenu(float width, float height)
{
	if (!font.loadFromFile("./Resources/moonhouse.ttf"))
	{
		// handle error
	}

	rect.setFillColor(sf::Color(0, 0, 0, 128));

	backgroundTexture.loadFromFile("./Resources/menu/border.png");
	backgroundSprite.setTexture(backgroundTexture);

	pointerTexture.loadFromFile("./Resources/menu/cat.png");
	pointerSprite.setTexture(pointerTexture);

	sfxSound.loadFromFile("./Resources/sfx/cat.ogg");
	sfx.setBuffer(sfxSound);

	sfxPause.loadFromFile("./Resources/sfx/confirm.ogg");
	pauseSound.setBuffer(sfxPause);

	menu[0].setFont(font);
	menu[0].setCharacterSize(16);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Resume Game");

	menu[1].setFont(font);
	menu[1].setCharacterSize(16);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("To Menu");

	menu[2].setFont(font);
	menu[2].setCharacterSize(16);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Exit Game");

	title.setFont(font);
	title.setCharacterSize(32);
	title.setColor(sf::Color::White);
	title.setString("Pauze");


	selectedItemIndex = 0;
}


PauseMenu::~PauseMenu()
{

}

void PauseMenu::draw(sf::RenderWindow &window)
{

	window.draw(rect);
	window.draw(backgroundSprite);
	window.draw(pointerSprite);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}

	window.draw(title);
}

void PauseMenu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		sfx.play();
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
		pointerSprite.setPosition(pointerSprite.getPosition().x, pointerSprite.getPosition().y - 18);
	}
}

void PauseMenu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		sfx.play();
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
		pointerSprite.setPosition(pointerSprite.getPosition().x, pointerSprite.getPosition().y + 18);
	}
}

int PauseMenu::KeyHandler()
{
	if (Input::GetKeyDown("Up"))
	{
		MoveUp();

	}
	if (Input::GetKeyDown("Down"))
	{
		MoveDown();
	}
	if (Input::GetKeyDown("Return"))
	{
		return GetPressedItem();
	}

	return -1;
}

void PauseMenu::setPositions(float levelx, float levely, float width, float height)
{

	selectedItemIndex = 0;
	menu[1].setColor(sf::Color::White);
	menu[2].setColor(sf::Color::White);
	menu[0].setColor(sf::Color::Red);


	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(levelx, levely);

	float x = levelx + width / 2 - 160;
	float y = levely + height / 2 - 185;
	backgroundSprite.setPosition(x, y);

	x += 110;
	y += 50;
	title.setPosition(sf::Vector2f(x, y));
	y += 48;
	x -= 30;
	menu[0].setPosition(sf::Vector2f(x, y));
	menu[1].setPosition(sf::Vector2f(x, y + 18));
	menu[2].setPosition(sf::Vector2f(x, y + 36));

	pointerSprite.setPosition(sf::Vector2f(x + 150, y));
}


