#include "stdafx.h"
#include "Context.h"
#include "MenuState.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>
#include "method_dispatcher.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>
#include "Input.h"


using namespace Awesomium;

void MenuState::run()
{

	sf::Event event;

	// Awesomium init
	MethodDispatcher dispatcher;
	WebCore* web_core = WebCore::Initialize(WebConfig());
	int i = 0;
	WebView* webView = web_core->CreateWebView(960, 640);

	//Bind
	std::cout << "binding" << std::endl;
	Awesomium::JSValue result = webView->CreateGlobalJavascriptObject(Awesomium::WSLit("app"));
	Awesomium::JSObject& app_object = result.ToObject();
	dispatcher.Bind(app_object,WSLit("app"),JSDelegate(this, &MenuState::OnSayHello));
	webView->set_js_method_handler(&dispatcher);

	// Load Page
	WebURL url(WSLit("file:///Resources/menuHTML/menu.html"));
	webView->LoadURL(url);
	webView->SetTransparent(true);

	while (webView->IsLoading())
		web_core->Update();

	Sleep(300);
	web_core->Update();

	//Create Bitmap
	BitmapSurface* surface = static_cast<Awesomium::BitmapSurface*>(webView->surface());
	sf::Texture uiTexture;
	uiTexture.create(960, 640);
	sf::Uint8* pixels = new sf::Uint8[960 * 640 * 4];

	while (context->window.isOpen()) {
		context->window.clear();

		while (context->window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				context->window.close();
		}

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			Input::EventOccured(event);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				std::cout << "up key pressed" << std::endl;
				
				WebURL url(WSLit("file:///Resources/menuHTML/menu.html"));
				webView->LoadURL(url);
				
				while (webView->IsLoading())
					web_core->Update();

				Sleep(300);
				web_core->Update();

				
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				std::cout << "down key pressed" << std::endl;
				
				WebURL url(WSLit("file:///Resources/menuHTML/menu2.html"));
				webView->LoadURL(url);
				//webView->ExecuteJavascript(WebString::CreateFromUTF8("myfunc()",9), WebString());

				WebKeyboardEvent keyEvent;
				keyEvent.type = WebKeyboardEvent::kTypeKeyDown;
				webView->InjectKeyboardEvent(keyEvent);

				while (webView->IsLoading())
					web_core->Update();

				Sleep(300);
				web_core->Update();
			}
		}

		// Create image from Bitmap
		surface = static_cast<Awesomium::BitmapSurface*>(webView->surface());
		const unsigned char* tempBuffer = surface->buffer();
		for (register int i = 0; i < 960 * 640 * 4; i += 4) {
			pixels[i] = tempBuffer[i + 2]; // B
			pixels[i + 1] = tempBuffer[i + 1]; // G
			pixels[i + 2] = tempBuffer[i]; // R
			pixels[i + 3] = tempBuffer[i + 3]; // Alpha
		}

		sf::Sprite ui(uiTexture);
		uiTexture.update(pixels);

		context->window.draw(ui);
		context->window.display();
	}
	
}

MenuState::MenuState(Context* c)
{
	this->context = c;
}


MenuState::~MenuState()
{
	delete context;
}