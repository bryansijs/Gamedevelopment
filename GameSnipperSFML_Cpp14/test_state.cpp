#include "stdafx.h"
#include "test_state.h"

bool gameOver = false;

void test_state::Initialize(sf::RenderWindow* window)
{
	/*manager = new Object_Manager();

	this->manager->Add("floor", "floor.png", false);
	this->manager->Get("floor")->body->SetTransform(b2Vec2(0, -480), 0);

	this->manager->Add("ball", "ship.png", true);
	this->manager->Get("ball")->body->SetTransform(b2Vec2(24, 0), 0);


	this->manager->Add("Character", "paddle1.png", true);
	this->manager->Get("Character")->body->SetTransform(b2Vec2(150, -150), 0);
	this->manager->Get("Character")->setSounds("");

	this->manager->Add("ball2", "ship.png", true);
	this->manager->Get("ball2")->body->SetTransform(b2Vec2(64, 0), 0);
	this->manager->Add("ball3", "ship.png", true);
	this->manager->Get("ball3")->body->SetTransform(b2Vec2(75, 40), 0);*/
}
void test_state::Update(sf::RenderWindow* window)
{
	/*
		this->manager->Get("Character")->Handle();

	


	if (!this->manager->Update(window))
	{
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		quitGame = true;
	}

	*/
}
void test_state::Render(sf::RenderWindow* window)
{
	//this->manager->Render(window);
}
void test_state::Destroy(sf::RenderWindow* window)
{
	delete this->manager;
}



