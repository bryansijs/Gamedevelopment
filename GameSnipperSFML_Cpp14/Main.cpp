#include "stdafx.h"
#include "game_state.h"
#include "test_state.h"
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono> 
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2d/Box2D.h>

#include "application.h"
#include "method_dispatcher.h"
#include "js_delegate.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/BitmapSurface.h>
#include "LevelImporter.h"
#include <string>


game_state coreState;
bool quitGame = false;
using namespace std;

bool doEvents = true;

bool moveDown = true;
int t_value = 0;
int t_max = 0;

bool moveRight = true;
int r_value = 0;
int r_max = 0;


void updateViewPort(sf::Vector2i &worldPos)
{
	//updateVP
	if (worldPos.y > 640)
	{
		doEvents = false;
		t_max += 320;
		moveDown = true;
	}

	if (worldPos.y < 0)
	{
		doEvents = false;
		t_max -= 320;
		moveDown = false;
	}

	if (worldPos.x > 960)
	{
		doEvents = false;
		r_max += 480;
		moveRight = true;
	}

	if (worldPos.x < 0)
	{
		doEvents = false;
		r_max -= 480;
		moveRight = false;
	}
}

void MoveView(sf::View &view)
{
	if (moveDown)
	{
		if (t_value < t_max)
		{
			view.move(0, 2.0f);
			t_value++;
		}
	}
	else
	{
		if (t_value > t_max)
		{
			view.move(0, -2.0f);
			t_value--;
		}
	}

	if (moveRight)
	{
		if (r_value < r_max)
		{
			view.move(2.0f, 0);
			r_value++;
		}
	}
	else
	{
		if (r_value > r_max)
		{
			view.move(-2.0f, 0);
			r_value--;
		}
	}

	sf::RenderWindow window(sf::VideoMode(960, 640), "Team Echo!");

	if (t_value == t_max && r_value == r_max)
	{
		doEvents = true;
	}
}

	// Awesomium
	WebCore* web_core = WebCore::Initialize(WebConfig());

	WebView* view = web_core->CreateWebView(960, 640, 0, kWebViewType_Offscreen);
	//BindMethods(view);

	WebURL url(WSLit("file:///Resources/menuHTML/menu.html"));
	view->LoadURL(url);

	view->SetTransparent(true);

	// Wait for our WebView to finish loading
	while (view->IsLoading())
		web_core->Update();

	// Sleep a bit and update once more to give scripts and plugins
	// on the page a chance to finish loading.
	Sleep(300);
	web_core->Update();

	BitmapSurface* surface = static_cast<BitmapSurface*>(view->surface());

	sf::Texture uiTexture;
	uiTexture.create(960, 640);

int _tmain(int argc, _TCHAR* argv[])
{
	LevelImporter* l = new LevelImporter();
	l->Import("./Resources/levels/Level_New.json");
	l->Prepare();

	sf::RenderWindow window(sf::VideoMode(960, 640), "Team Echo!");
	sf::FloatRect rect(0, 0, 960, 640);
	sf::View view;


	std::cout << "Debug menu laat fouten zien." << std::endl;

	sf::Keyboard::Key d = sf::Keyboard::Key();
	sf::Uint8* pixels = new sf::Uint8[960 * 640 * 50];

	sf::CircleShape shape(25.0f);
	shape.setFillColor(sf::Color::Magenta);
	shape.setPosition(50, 50);

	view.reset(rect);
	window.setView(view);
	l->Start(&shape);

	while (window.isOpen())
	{
		window.clear();

		l->Draw(&window);
		l->Update();
		MoveView(view);
		
		sf::Vector2f s = shape.getPosition();
		sf::Vector2i worldPos = window.mapCoordsToPixel(s);

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		std::this_thread::sleep_for(std::chrono::milliseconds(10));


		window.clear();
		
		const unsigned char* tempBuffer = surface->buffer();

		for (register int i = 0; i < 960 * 640 * 4; i += 4) {
			pixels[i] = tempBuffer[i + 2]; // B
			pixels[i + 1] = tempBuffer[i + 1]; // G
			pixels[i + 2] = tempBuffer[i]; // R
			pixels[i + 3] = tempBuffer[i + 3]; // Alpha
		}

		coreState.Update();
		coreState.Render();

		for (int i = 0; i < 9; i++)
		{
			if (bulletList[i].getPosition().x >= 0)
			{
				window.draw(bulletList[i]);
			}
		}

		

		sf::Sprite ui(uiTexture);
		uiTexture.update(pixels);

		window.draw(ui);
		window.display();
	}

	view->Destroy();
	WebCore::Shutdown();

	delete[] pixels;

		if (doEvents) {
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				{
					t_max += 160;
					moveDown = true;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					t_max -= 160;
					moveDown = false;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					shape.setPosition(shape.getPosition().x, shape.getPosition().y - 10);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					shape.setPosition(shape.getPosition().x, shape.getPosition().y + 10);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					shape.setPosition(shape.getPosition().x - 10, shape.getPosition().y);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					shape.setPosition(shape.getPosition().x + 10, shape.getPosition().y);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
					cout << "x: " << worldPos.x << " y: " << worldPos.y << endl;
				}

				updateViewPort(worldPos);
			}
		}

		window.setView(view);
		window.draw(shape);
		window.display();
	}

	return 0;
}

