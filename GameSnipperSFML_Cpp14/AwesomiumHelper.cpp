#include "stdafx.h"
#include "AwesomiumHelper.h"
#include <Awesomium/STLHelpers.h>

AwesomiumHelper::AwesomiumHelper(WebCore* webcore, std::string path, int width, int height)
{
	AwesomiumHelper::webcore = webcore;
	AwesomiumHelper::path = path.c_str();
	AwesomiumHelper::width = width;
	AwesomiumHelper::height = height;

	webview = webcore->CreateWebView(width, height);

	ReloadPage();

	surface = static_cast<BitmapSurface*>(webview->surface());
	texture.create(width, height);
	pixels = new sf::Uint8[width * height * 4];
}

AwesomiumHelper::~AwesomiumHelper()
{
}

void AwesomiumHelper::ReloadPage()
{
	WebURL url(WSLit(path));
	webview->LoadURL(url);
	webview->SetTransparent(true);

	while (webview->IsLoading())
	{
		webcore->Update();
	}
	Sleep(100);
	webcore->Update();
}

void AwesomiumHelper::CreateBitmap()
{
	const unsigned char* tempBuffer = surface->buffer();

	for (register int i = 0; i < width * height * 4; i += 4) {
		pixels[i] = tempBuffer[i + 2]; // B
		pixels[i + 1] = tempBuffer[i + 1]; // G
		pixels[i + 2] = tempBuffer[i]; // R
		pixels[i + 3] = tempBuffer[i + 3]; // Alpha
	}

	sprite = sf::Sprite(texture);
	texture.update(pixels);
}

sf::Sprite AwesomiumHelper::GetSprite()
{
	CreateBitmap();
	return sprite;
}

void AwesomiumHelper::JavaScriptCall(std::string functionName, std::string parameter)
{
	JSValue window = webview->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));

	if (window.IsObject())
	{
		JSArray args;
		const char * param = parameter.c_str();
		WebString string = WebString::CreateFromUTF8(param, strlen(param) + 1);
		JSValue val = JSValue(string);
		args.Push(val);
		window.ToObject().Invoke(WSLit(functionName.c_str()), args);
	}

	Sleep(50);
	webcore->Update();

}

void AwesomiumHelper::JavaScriptCall(std::string functionName, int parameter)
{
	JSValue window = webview->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));

	if (window.IsObject())
	{
		JSArray args;
		JSValue val = JSValue(parameter);
		args.Push(val);
		window.ToObject().Invoke(WSLit(functionName.c_str()), args);
	}
	Sleep(50);
	webcore->Update();
}