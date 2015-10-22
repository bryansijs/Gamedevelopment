#include "stdafx.h"
#include "Context.h"
#include "MenuState.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>
#include "js_delegate.h"
#include "method_dispatcher.h"
#include "application.h"


using namespace Awesomium;

Application* app_;
MethodDispatcher method_dispatcher_;

void BindMethods(WebView* web_view) {
	// Create a global js object named 'app'
	JSValue result = web_view->CreateGlobalJavascriptObject(WSLit("app"));
	if (result.IsObject()) {
		// Bind our custom method to it.
		JSObject& app_object = result.ToObject();
		method_dispatcher_.Bind(app_object,
			WSLit("sayHello"),
			JSDelegate(this, &this->OnSayHello));
	}

	// Bind our method dispatcher to the WebView
	web_view->set_js_method_handler(&method_dispatcher_);
}

// Bound to app.sayHello() in JavaScript
void OnSayHello(WebView* caller,
	const JSArray& args) {
	app_->ShowMessage("Hello!");
}

void MenuState::run()
{
	// Awesomium init
	WebCore* web_core = WebCore::Initialize(WebConfig());
	int i = 0;
	WebView* webView = web_core->CreateWebView(960, 640);

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

		// Create image from Bitmap
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
}
