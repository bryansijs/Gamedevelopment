#pragma once
#include <Awesomium/WebCore.h>
#include <Awesomium/WebString.h>
#include <iostream>

class JSConsole : public Awesomium::WebViewListener::View
{
public:
	void OnChangeTitle(Awesomium::WebView* caller, const Awesomium::WebString& title) override {};
	void OnChangeAddressBar(Awesomium::WebView* caller, const Awesomium::WebURL& url) override {};
	void OnChangeTooltip(Awesomium::WebView* caller, const Awesomium::WebString& tooltip) override{};
	void OnChangeTargetURL(Awesomium::WebView* caller, const Awesomium::WebURL& url) override {};
	void OnChangeCursor(Awesomium::WebView* caller, Awesomium::Cursor cursor) override {};
	void OnChangeFocus(Awesomium::WebView* caller, Awesomium::FocusedElementType focused_type) override{};
	void OnShowCreatedWebView(Awesomium::WebView* caller, Awesomium::WebView* new_view, const Awesomium::WebURL& opener_url, const Awesomium::WebURL& target_url, const Awesomium::Rect& initial_pos, bool is_popup) override {};
	void OnAddConsoleMessage(Awesomium::WebView* caller, const Awesomium::WebString& message, int line_number, const Awesomium::WebString& source) override { std::cout << "console.log: " << message;};
	
	JSConsole()
	{
	}

	~JSConsole()
	{
	}
};

