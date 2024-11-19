#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_client.h"

// Implement a simple client for the browser.
class SimpleHandler : public CefClient, public CefLifeSpanHandler {
public:
    SimpleHandler() = default;
    
    // Create a new browser instance
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {
        CefLifeSpanHandler::OnAfterCreated(browser);
        browser_ = browser;
    }

    // Close the browser when needed
    void CloseAllBrowsers(bool force_close) {
        if (browser_) browser_->GetHost()->CloseBrowser(force_close);
    }

    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
        return this;
    }

private:
    CefRefPtr<CefBrowser> browser_;

    IMPLEMENT_REFCOUNTING(SimpleHandler);
};

// Main entry point function
int main(int argc, char* argv[]) {
    // Structure for CEF settings
    CefMainArgs main_args(argc, argv);
    CefRefPtr<CefApp> app;
    
    // Initialize CEF with settings
    CefSettings settings;
    settings.no_sandbox = true; // Disable sandboxing for simplicity
    CefInitialize(main_args, settings, app.get(), nullptr);

    // Specify URL for the initial browser window
    CefBrowserSettings browser_settings;
    CefWindowInfo window_info;
    window_info.SetAsPopup(nullptr, "CEF Browser");

    // Create the browser window
    CefRefPtr<SimpleHandler> handler(new SimpleHandler());
    CefBrowserHost::CreateBrowser(window_info, handler, "https://www.google.com", browser_settings, nullptr);

    // Run the CEF message loop
    CefRunMessageLoop();

    // Shutdown CEF
    CefShutdown();

    return 0;
}
