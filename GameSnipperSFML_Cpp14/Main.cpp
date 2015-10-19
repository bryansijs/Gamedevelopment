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

using namespace Awesomium;	

int _tmain(int argc, _TCHAR* argv[])
{
	// Awesomium
	WebCore* web_core = WebCore::Initialize(WebConfig());

	WebView* AWview = web_core->CreateWebView(960, 640, 0, kWebViewType_Offscreen);
	//BindMethods(view);

	WebURL url(WSLit("file:///Resources/menuHTML/menu.html"));
	AWview->LoadURL(url);
	AWview->SetTransparent(true);

	// Wait for our WebView to finish loading
	while (AWview->IsLoading())
		web_core->Update();

	// Sleep a bit and update once more to give scripts and plugins
	// on the page a chance to finish loading.
	Sleep(300);
	web_core->Update();

	BitmapSurface* surface = static_cast<BitmapSurface*>(AWview->surface());

	sf::Texture uiTexture;
	uiTexture.create(960, 640);

	sf::RenderWindow window(sf::VideoMode(960, 640), "Team Echo!");

	std::cout << "Debug menu laat fouten zien." << std::endl;

	sf::Keyboard::Key d = sf::Keyboard::Key();
	sf::Uint8* pixels = new sf::Uint8[960 * 640 * 50];

	sf::CircleShape shape(25.0f);
	shape.setFillColor(sf::Color::Magenta);
	shape.setPosition(50, 50);

	coreState.SetWindow(&window);

	while (window.isOpen())
	{
		window.clear();

		window.draw(shape);
		
		
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
		

		sf::Sprite ui(uiTexture);
		uiTexture.update(pixels);

		window.draw(ui);
		window.display();
	}

	AWview->Destroy();
	WebCore::Shutdown();
	delete[] pixels;

	return 0;
}

