// GameSnippet.cpp : Defines the entry point for the console application.
//

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


game_state coreState;
bool quitGame = false;

using namespace Awesomium;

Application* app_;
MethodDispatcher method_dispatcher_;

//void BindMethods(WebView* web_view) {
//	// Create a global js object named 'app'
//	JSValue result = web_view->CreateGlobalJavascriptObject(WSLit("app"));
//	if (result.IsObject()) {
//		// Bind our custom method to it.
//		JSObject& app_object = result.ToObject();
//		method_dispatcher_.Bind(app_object,
//			WSLit("sayHello"),
//			JSDelegate(this, &Main::OnSayHello));
//	}
//
//	// Bind our method dispatcher to the WebView
//	web_view->set_js_method_handler(&method_dispatcher_);
//}
//
//// Bound to app.sayHello() in JavaScript
//void OnSayHello(WebView* caller,
//	const JSArray& args) {
//	app_->ShowMessage("Hello!");
//}

int _tmain(int argc, _TCHAR* argv[])
{


	sf::Texture bulletTexture;
	bulletTexture.loadFromFile("Resources/sprites/bullet.png");
	sf::Sprite shapey(bulletTexture);

	int bulletSpeed(20);
	sf::Sprite bulletList[10];



	sf::RenderWindow window(sf::VideoMode(640, 480), "Team Echo!");


	coreState.SetWindow(&window);
	coreState.SetState(new test_state());

	// Awesomium
	WebCore* web_core = WebCore::Initialize(WebConfig());

	WebView* view = web_core->CreateWebView(640, 480, 0, kWebViewType_Offscreen);
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
	uiTexture.create(640, 480);

	sf::Texture menuTexture;
	menuTexture.loadFromFile("Resources/background/backgroundd.png");

	sf::CircleShape shape(100.f);
	shape.setPosition(400, 100);
	sf::Font font;
	font.loadFromFile("Resources/arial.ttf");
	shape.setFillColor(sf::Color::Cyan);
	std::cout << "Debug menu laat fouten zien." << std::endl;

	sf::Text text;
	sf::Music Music1;

	if (!Music1.openFromFile("Resources/music/overworld.ogg"))
	{
		std::cout << "Music not found" << std::endl;
	}
	
	Music1.play();
	// select the font
	text.setFont(font); // font is a sf::Font
	text.setPosition(180, 160);
	// set the string to display
	text.setString("Welcome team\nEcho");
	// set the character size
	text.setCharacterSize(24); // in pixels, not points!
	// set the color
	text.setColor(sf::Color::White);
	text.setRotation(20);
	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	sf::Keyboard::Key d = sf::Keyboard::Key();
	sf::Uint8* pixels = new sf::Uint8[640 * 480 * 4];

	while (window.isOpen())
	{

		sf::Sprite sprite(menuTexture);
 
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
				{
					shape.setFillColor(sf::Color::Cyan);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
				{
					shape.setFillColor(sf::Color::White);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
				{
					shape.setFillColor(sf::Color::Red);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
				{
					shape.setFillColor(sf::Color::Green);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
				{
					shape.setFillColor(sf::Color::Yellow);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
				{
					shape.setFillColor(sf::Color::Blue);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
				{
					shape.setFillColor(sf::Color::Black);
				}


				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{

					for (int i = 0; i < 10; i++)
					{
						if (bulletList[i].getPosition().x < 0)
						{
							bulletList[i].setTexture(bulletTexture);
							bulletList[i].setPosition(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius() / 2);
					
							break;
						}
					}

				}


			}
		}



		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		for (int i = 0; i < 9; i++)
		{
			if (bulletList[i].getPosition().x >= 0)
			{
				bulletList[i].setPosition(bulletList[i].getPosition().x + bulletSpeed, bulletList[i].getPosition().y);

				if (bulletList[i].getPosition().x > window.getSize().x)
				{
					bulletList[i].setPosition(-100, -100);
				}
			}
		}


		window.clear();

	
		window.draw(sprite);
		window.draw(shape);
		window.draw(text);

		coreState.Update();
		coreState.Render();

		for (int i = 0; i < 9; i++)
		{
			if (bulletList[i].getPosition().x >= 0)
			{
				window.draw(bulletList[i]);
			}
		}

		const unsigned char* tempBuffer = surface->buffer();

		for (register int i = 0; i < 640 * 480 * 4; i += 4) {
			pixels[i] = tempBuffer[i + 2]; // B
			pixels[i + 1] = tempBuffer[i + 1]; // G
			pixels[i + 2] = tempBuffer[i]; // R
			pixels[i + 3] = tempBuffer[i + 3]; // Alpha
		}

		sf::Sprite ui(uiTexture);
		uiTexture.update(pixels);

		window.draw(ui);

		window.display();
	}

	view->Destroy();
	WebCore::Shutdown();

	delete[] pixels;

	return 0;
}

