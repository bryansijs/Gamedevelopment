#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Awesomium/WebView.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/WebCore.h>

using namespace Awesomium;

class AwesomiumHelper
{
public:
	AwesomiumHelper(WebCore* webcore, std::string path, int width, int height);
	~AwesomiumHelper();
	sf::Sprite GetSprite();
	void JavaScriptCall(std::string functionName, int parameter);
	void JavaScriptCall(std::string functionName, std::string parameter);
private:
	int width;
	int height;
	char const* path;

	WebCore* webcore;
	WebView* webview;
	BitmapSurface* surface;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Uint8* pixels;

	void ReloadPage();
	void CreateBitmap();
};