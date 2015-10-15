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



	sf::RenderWindow window(sf::VideoMode(960, 640), "Team Echo!");


	coreState.SetWindow(&window);
	coreState.SetState(new test_state());

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

	sf::Texture menuTexture;
	menuTexture.loadFromFile("Resources/background/backgroundd.png");

	std::cout << "Debug menu laat fouten zien." << std::endl;

	sf::Keyboard::Key d = sf::Keyboard::Key();
	sf::Uint8* pixels = new sf::Uint8[960 * 640 * 50];

	while (window.isOpen())
	{

		sf::Sprite sprite(menuTexture);
 
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

	return 0;
}

